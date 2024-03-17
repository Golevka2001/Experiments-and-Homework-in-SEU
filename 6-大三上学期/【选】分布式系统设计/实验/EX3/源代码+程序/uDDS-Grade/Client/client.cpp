/**********************************************************
*****************  客户端程序 client.cpp  *******************
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "conio.h"

/* IDL_TypeSupport.h中包含所有依赖的头文件 */
#include "IDL_TypeSupport.h"

#define MAX_STR_LEN 32

/* AverageGradeListener继承于DataReaderListener，
   需要重写其继承过来的方法on_data_available()，在其中进行数据监听读取操作 */
class AverageGradeListener : public DataReaderListener {
public:
	virtual void on_data_available(DataReader* reader);
};

/* 重写继承过来的方法on_data_available()，在其中进行数据监听读取操作 */
void AverageGradeListener::on_data_available(DataReader* reader)
{
	AverageGradeDataReader * AverageGrade_reader = NULL;
	AverageGradeSeq data_seq;
	SampleInfoSeq info_seq;
	ReturnCode_t retcode;
	int i;

	/* 利用reader，创建一个读取AverageGrade类型的AverageGrade_reader*/
	AverageGrade_reader = AverageGradeDataReader::narrow(reader);
	if (AverageGrade_reader == NULL) {
		fprintf(stderr, "DataReader narrow error\n");
		return;
	}

	/* 获取数据，存放至data_seq，data_seq是一个队列 */
	retcode = AverageGrade_reader->read(
		data_seq, info_seq, 10, 0, 0, 0);

	if (retcode == RETCODE_NO_DATA) {
		return;
	}
	else if (retcode != RETCODE_OK) {
		fprintf(stderr, "take error %d\n", retcode);
		return;
	}

	/* 打印数据 */
	for (i = 0; i < data_seq.length(); ++i) {
		cout << "\nreceive data:" << endl
			<< " - average score: "
			<< data_seq[i].avg_score << endl
			<< " - students' id: "
			<< data_seq[i].id1 << ", "
			<< data_seq[i].id2 << ", "
			<< data_seq[i].id3 << endl;

         delete data_seq[i].id1;
		 delete data_seq[i].id2;
		 delete data_seq[i].id3;
         data_seq[i].id1 = NULL;
		 data_seq[i].id2 = NULL;
		 data_seq[i].id3 = NULL;
	}
}

/* 删除所有实体 */
static int client_shutdown(
	DomainParticipant *participant)
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

/* 客户端执行函数 */
extern "C" int client_main(int domainId)
{
	DomainParticipant *participant = NULL;
	Subscriber *subscriber = NULL;
	Publisher* publisher = NULL;
	Topic *recv_topic = NULL;
	Topic* send_topic = NULL;
	DataReader *reader = NULL;
	DataWriter* writer = NULL;
	AverageGradeListener* reader_listener = NULL;
	GradeDataWriter* Grade_writer = NULL;
	ReturnCode_t recv_retcode;
	ReturnCode_t send_retcode;
	Grade* instance = NULL;
	InstanceHandle_t instance_handle = HANDLE_NIL;
	const char *recv_type_name = NULL;
	const char* send_type_name = NULL;
	int status = 0;


	/* 创建一个participant */
	participant = DomainParticipantFactory::get_instance()->create_participant(
		domainId, PARTICIPANT_QOS_DEFAULT/* participant默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (participant == NULL) {
		fprintf(stderr, "create_participant error\n");
		client_shutdown(participant);
		return -1;
	}

	/* 创建一个subscriber */
	subscriber = participant->create_subscriber(
		SUBSCRIBER_QOS_DEFAULT/* 默认QoS */,
		NULL /* listener */, STATUS_MASK_NONE);
	if (subscriber == NULL) {
		fprintf(stderr, "create_subscriber error\n");
		client_shutdown(participant);
		return -1;
	}
	/* 创建一个publisher */
	publisher =
		participant->create_publisher(PUBLISHER_QOS_DEFAULT /* 默认QoS */,
			NULL /* listener */, STATUS_MASK_NONE);
	if (publisher == NULL)
	{
		fprintf(stderr, "create_publisher error\n");
		client_shutdown(participant);
		return -1;
	}

	/* 注册数据类型 */
	recv_type_name = AverageGradeTypeSupport::get_type_name();
	recv_retcode = AverageGradeTypeSupport::register_type(
		participant, recv_type_name);
	if (recv_retcode != RETCODE_OK) {
		fprintf(stderr, "register_type(receive) error %d\n", recv_retcode);
		client_shutdown(participant);
		return -1;
	}
	send_type_name = GradeTypeSupport::get_type_name();
	send_retcode = GradeTypeSupport::register_type(participant, send_type_name);
	if (send_retcode != RETCODE_OK)
	{
		fprintf(stderr, "register_type(send) error %d\n", send_retcode);
		client_shutdown(participant);
		return -1;
	}

	/* 创建接收主题 */
	recv_topic = participant->create_topic(
		"tpc_AvgGrade"/* 主题名 */,
		recv_type_name, TOPIC_QOS_DEFAULT/* 默认QoS */, 
		NULL /* listener */, STATUS_MASK_NONE);
	if (recv_topic == NULL) {
		fprintf(stderr, "create_topic(receive) error\n");
		client_shutdown(participant);
		return -1;
	}

	/* 创建发送主题 */
	send_topic = participant->create_topic(
		"tpc_Grade" /* 主题名 */, send_type_name /* 类型名 */,
		TOPIC_QOS_DEFAULT /* 默认QoS */, NULL /* listener */, STATUS_MASK_NONE);
	if (send_topic == NULL)
	{
		fprintf(stderr, "create_topic(send) error\n");
		client_shutdown(participant);
		return -1;
	}

	/* 创建一个监听器 */
	reader_listener = new AverageGradeListener();

	/* 创建datareader，并定制datareader的QoS */
	reader = subscriber->create_datareader(
		recv_topic, DATAREADER_QOS_DEFAULT/* 默认QoS */,
		reader_listener/* listener */, STATUS_MASK_ALL);
	if (reader == NULL) {
		fprintf(stderr, "create_datareader error\n");
		client_shutdown(participant);
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
		client_shutdown(participant);
		return -1;
	}
	Grade_writer = GradeDataWriter::narrow(writer);
	if (Grade_writer == NULL)
	{
		fprintf(stderr, "DataWriter narrow error\n");
		client_shutdown(participant);
		return -1;
	}

	/* 主循环 ，监听器会默认调用on_data_available()监听数据 */
	while (true)
	{
		/* 检测到键盘输入时暂停 */
		if (_kbhit())
		{
			char command[MAX_STR_LEN] = {};
			cin.getline(command, MAX_STR_LEN);

			/* 输入“:quit”结束运行 */
			if (!strcmp(command, ":quit"))
				break;
			/* 输入“:score”发送一名学生的信息 */
			if (!strcmp(command, ":score"))
			{
				/* 录入部分 */
				char temp_name[MAX_STR_LEN] = {};
				char temp_id[MAX_STR_LEN] = {};
				float temp_score = 0.0;
				cout << "\nplease enter a student's infomation:\n";
				cout << " - name: ";
				cin.getline(temp_name, MAX_STR_LEN);
				cout << " - student id: ";
				cin.getline(temp_id, MAX_STR_LEN);
				cout << " - score: ";
				cin >> temp_score;
				getchar();  // 多余的换行符

				/* 发送部分 */
				/* 创建一个数据样本 */
				instance = GradeTypeSupport::create_data();
				if (instance == NULL)
				{
					fprintf(stderr, "GradeTypeSupport::create_data error\n");
					break;
				}

				/* 发送数据 */
				instance->name = new char[MAX_STR_LEN];
				instance->id = new char[MAX_STR_LEN];
				strcpy_s(instance->name, strlen(temp_name) + 1, temp_name);
				strcpy_s(instance->id, strlen(temp_id) + 1, temp_id);
				instance->score = temp_score;

				send_retcode = Grade_writer->write(*instance, instance_handle);
				if (send_retcode != RETCODE_OK)
				{
					fprintf(stderr, "write error %d\n", send_retcode);
				}
				else
					fprintf(stderr, "\nwrite successfully\n\n");

				/* 删除数据样本 */
				send_retcode = GradeTypeSupport::delete_data(instance);
				if (send_retcode != RETCODE_OK)
				{
					fprintf(stderr, "GradeTypeSupport::delete_data error %d\n", send_retcode);
				}
			}
			else
				cout << "unknown command \"" << command << "\"\n";
		}
	}

	/* 删除所有实体和监听器 */
	status = client_shutdown(participant);
	delete reader_listener;

	return status;
}

int main(int argc, char *argv[])
{
	int domain_id = 0;

	if (argc >= 2) {
		domain_id = atoi(argv[1]);/* 发送至域domain_id */
	}

	return client_main(domain_id);
}
