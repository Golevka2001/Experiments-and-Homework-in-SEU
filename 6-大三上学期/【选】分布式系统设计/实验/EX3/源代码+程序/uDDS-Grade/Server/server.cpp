/**********************************************************
****************  服务器端程序 server.cpp  *******************
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "conio.h"

/* IDL_TypeSupport.h中包含所有依赖的头文件 */
#include "IDL_TypeSupport.h"

#define MAX_STU_NUM 3  /* 最大学生信息存储数 */
#define MAX_STR_LEN 32

int stu_cnt = 0;  /* 当前已存储学生信息数 */
struct Grade students[MAX_STU_NUM];  /* 存储学生信息 */


/* GradeListener继承于DataReaderListener，
   需要重写其继承过来的方法on_data_available()，在其中进行数据监听读取操作 */
class GradeListener : public DataReaderListener {
public:
	virtual void on_data_available(DataReader* reader);
};

/* 重写继承过来的方法on_data_available()，在其中进行数据监听读取操作 */
void GradeListener::on_data_available(DataReader* reader)
{
	GradeDataReader* Grade_reader = NULL;
	GradeSeq data_seq;
	SampleInfoSeq info_seq;
	ReturnCode_t retcode;

	/* 利用reader，创建一个读取Grade类型的Grade_reader*/
	Grade_reader = GradeDataReader::narrow(reader);
	if (Grade_reader == NULL) {
		fprintf(stderr, "DataReader narrow error\n");
		return;
	}

	/* 获取数据，存放至data_seq，data_seq是一个队列 */
	retcode = Grade_reader->read(
		data_seq, info_seq, 10, 0, 0, 0);

	if (retcode == RETCODE_NO_DATA) {
		return;
	}
	else if (retcode != RETCODE_OK) {
		fprintf(stderr, "take error %d\n", retcode);
		return;
	}

	/* 将接收到的学生信息存储至全局变量students[]中 */
	students[stu_cnt].name = new char[MAX_STR_LEN];
	students[stu_cnt].id = new char[MAX_STR_LEN];
	strcpy_s(students[stu_cnt].name, sizeof(data_seq[0].name) + 1, data_seq[0].name);
	strcpy_s(students[stu_cnt].id, sizeof(data_seq[0].id) + 1, data_seq[0].id);
	students[stu_cnt].score = data_seq[0].score;

	/* 打印已存储的学生信息 */
	cout << "\nstudents' information:" << endl;
	for (int i = 0; i < stu_cnt + 1; ++i)
	{
		cout << " - student_" << i << ":\n"
			<< "  - name: " << students[i].name << endl
			<< "  - student id: " << students[i].id << endl
			<< "  - score: " << students[i].score << endl;
	}

	++stu_cnt;

	/* 将分配的空间释放 */
	for (int i = 0; i < data_seq.length(); ++i)
	{
		delete data_seq[i].name;
		delete data_seq[i].id;
		data_seq[i].name = NULL;
		data_seq[i].id = NULL;
	}
}

/* 删除所有实体 */
static int server_shutdown(
	DomainParticipant* participant)
{
	ReturnCode_t retcode;
	int status = 0;

	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_contained_entities error %d\n", retcode);
			status = -1;
		}

		retcode = DomainParticipantFactory::get_instance()->delete_participant(participant);
		if (retcode != RETCODE_OK) {
			fprintf(stderr, "delete_participant error %d\n", retcode);
			status = -1;
		}
	}
	return status;
}

/* 服务器端执行函数 */
extern "C" int server_main(int domainId)
{
	DomainParticipant* participant = NULL;
	Subscriber* subscriber = NULL;
	Publisher* publisher = NULL;
	Topic* recv_topic = NULL;
	Topic* send_topic = NULL;
	DataReader* reader = NULL;
	DataWriter* writer = NULL;
	GradeListener* reader_listener = NULL;
	AverageGradeDataWriter* AverageGrade_writer = NULL;
	ReturnCode_t recv_retcode;
	ReturnCode_t send_retcode;
	AverageGrade* instance = NULL;
	InstanceHandle_t instance_handle = HANDLE_NIL;
	const char* recv_type_name = NULL;
	const char* send_type_name = NULL;
	int status = 0;


	/* 创建一个participant */
	participant = DomainParticipantFactory::get_instance()->create_participant(
		domainId, PARTICIPANT_QOS_DEFAULT/* participant默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (participant == NULL) {
		fprintf(stderr, "create_participant error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 创建一个subscriber */
	subscriber = participant->create_subscriber(
		SUBSCRIBER_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (subscriber == NULL) {
		fprintf(stderr, "create_subscriber error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 创建一个publisher */
	publisher =
		participant->create_publisher(PUBLISHER_QOS_DEFAULT /* 默认QoS */,
			NULL /* listener */, STATUS_MASK_NONE);
	if (publisher == NULL)
	{
		fprintf(stderr, "create_publisher error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 注册数据类型 */
	recv_type_name = GradeTypeSupport::get_type_name();
	recv_retcode = GradeTypeSupport::register_type(
		participant, recv_type_name);
	if (recv_retcode != RETCODE_OK) {
		fprintf(stderr, "register_type error %d\n", recv_retcode);
		server_shutdown(participant);
		return -1;
	}
	send_type_name = AverageGradeTypeSupport::get_type_name();
	send_retcode = AverageGradeTypeSupport::register_type(participant, send_type_name);
	if (send_retcode != RETCODE_OK)
	{
		fprintf(stderr, "register_type error %d\n", send_retcode);
		server_shutdown(participant);
		return -1;
	}

	/* 创建接收主题 */
	recv_topic = participant->create_topic(
		"tpc_Grade"/* 主题名 */,
		recv_type_name, TOPIC_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (recv_topic == NULL) {
		fprintf(stderr, "create_topic error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 创建发送主题 */
	send_topic = participant->create_topic(
		"tpc_AvgGrade" /* 主题名 */, send_type_name /* 类型名 */,
		TOPIC_QOS_DEFAULT /* 默认QoS */, NULL /* listener */, STATUS_MASK_NONE);
	if (send_topic == NULL)
	{
		fprintf(stderr, "create_topic error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 创建一个监听器 */
	reader_listener = new GradeListener();

	/* 创建datareader，并定制datareader的QoS */
	reader = subscriber->create_datareader(
		recv_topic, DATAREADER_QOS_DEFAULT/* 默认QoS */,
		reader_listener/* listener */, STATUS_MASK_ALL);
	if (reader == NULL) {
		fprintf(stderr, "create_datareader error\n");
		server_shutdown(participant);
		delete reader_listener;
		return -1;
	}

	/* 创建datawriter，并定制datawriter的QoS  */
	writer =
		publisher->create_datawriter(send_topic, DATAWRITER_QOS_DEFAULT /* 默认QoS */,
			NULL /* listener */, STATUS_MASK_NONE);
	if (writer == NULL)
	{
		fprintf(stderr, "create_datawriter error\n");
		server_shutdown(participant);
		return -1;
	}
	AverageGrade_writer = AverageGradeDataWriter::narrow(writer);
	if (AverageGrade_writer == NULL)
	{
		fprintf(stderr, "DataWriter narrow error\n");
		server_shutdown(participant);
		return -1;
	}

	/* 主循环 ，监听器会默认调用on_data_available()监听数据 */
	while (true) {
		if (stu_cnt == 3)
		{
			/* 发送部分 */
			/* 创建一个数据样本 */
			instance = AverageGradeTypeSupport::create_data();
			if (instance == NULL)
			{
				fprintf(stderr, "AverageGradeTypeSupport::create_data error\n");
				server_shutdown(participant);
				return -1;
			}

			/* 发送数据 */
			float sum = 0;
			for (int i = 0; i < MAX_STU_NUM; ++i)
				sum += students[i].score;
			instance->avg_score = sum / MAX_STU_NUM;
			instance->id1 = new char[MAX_STR_LEN];
			instance->id2 = new char[MAX_STR_LEN];
			instance->id3 = new char[MAX_STR_LEN];
			strcpy_s(instance->id1, strlen(students[0].id) + 1, students[0].id);
			strcpy_s(instance->id2, strlen(students[1].id) + 1, students[1].id);
			strcpy_s(instance->id3, strlen(students[2].id) + 1, students[2].id);

			send_retcode = AverageGrade_writer->write(*instance, instance_handle);
			if (send_retcode != RETCODE_OK)
			{
				fprintf(stderr, "write error %d\n", send_retcode);
			}
			else
				fprintf(stderr, "\nwrite successfully\n\n");

			/* 删除数据样本 */
			send_retcode = AverageGradeTypeSupport::delete_data(instance);
			if (send_retcode != RETCODE_OK)
			{
				fprintf(stderr, "AverageGradeTypeSupport::delete_data error %d\n", send_retcode);
			}

			stu_cnt = 0;
			for (int i = 0; i < MAX_STU_NUM; ++i)
			{
				delete students[i].name;
				delete students[i].id;
				students[i].name = NULL;
				students[i].id = NULL;
			}
		}

		/* 检测到键盘输入时暂停 */
		if (_kbhit())
		{
			char command[MAX_STR_LEN] = {};
			cin.getline(command, MAX_STR_LEN);

			/* 输入“:quit”结束运行 */
			if (!strcmp(command, ":quit"))
			{
				server_shutdown(participant);
				return 0;
			}
			else
				cout << "unknown command \"" << command << "\"\n";
		}
	}

	/* 删除所有实体和监听器 */
	status = server_shutdown(participant);
	delete reader_listener;

	return status;
}

int main(int argc, char* argv[])
{
	int domain_id = 0;

	if (argc >= 2) {
		domain_id = atoi(argv[1]);/* 发送至域domain_id */
	}

	return server_main(domain_id);
}
