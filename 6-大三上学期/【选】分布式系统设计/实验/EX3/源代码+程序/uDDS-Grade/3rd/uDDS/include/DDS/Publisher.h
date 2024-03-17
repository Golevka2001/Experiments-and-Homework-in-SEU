/************************************************************
** 文件名：Publisher.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：Publisher头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _Publisher_H_
#define _Publisher_H_

/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"

/* Nephalem 系统头文件 */

/* Nephalem 前置声明 */
class PublisherImpl;
class DataWriterListener;

class DDS_DLL Publisher
{
public:
	//构造函数
	Publisher(PublisherImpl* pPublisherImpl);
	//析构函数
	virtual ~Publisher(void);
public:
	/* JDXCZ 此处为规范中定义的接口 */

	/* JDXCZ 创建数据写者 */
	DataWriter* create_datawriter(Topic* pTopic, const DataWriterQos& Qos, DataWriterListener * pDataWriterListener, StatusMask mask);

	/* JDXCZ 删除数据写者 */
	ReturnCode_t delete_datawriter(DataWriter* pDataWriter);

	/* JDXCZ 查找数据写者 */
	_DATA_WRITER_LIST_T  lookup_datawriter(const string& topic_name);

	///* JDXCZ 告诉DDS服务，应用将对属于本Publisher的DataWriter对象进行多次修改 */
	//ReturnCode_t suspend_publications();

	///* JDXCZ	告知服务，应用程序已完成之前suspend_publications方法启动的多个修改，
	//			服务实现者可以使用这种提示批量处理自suspend_publications以来所做的所有修改*/
	//ReturnCode_t resume_pulications();

	///* JDXCZ 要求应用程序使用属于Publisher的DataWriter对象开始“一致集”的修改 */
	//ReturnCode_t begin_coherent_changes();

	///* JDXCZ 终结由begin_coherent_changes方法的启动的“一致集” */
	//ReturnCode_t end_coherent_changes();

	///* JDXCZ	阻塞调用线程，直到所有匹配的可靠的DataReader实体都确认收到可靠的DataWriter实体写入的所有数据
	//			或者max_wait参数设定的持续时间已经到期 */
	//ReturnCode_t wait_for_acknowledgments(Duration_t max_wait);

	/* JDXCZ    返回Publisher所属的Domainparticipant */
	DomainParticipant* get_participant();

	///* JDXCZ    删除Publisher对象创建的所有实体，删除所有包含的DataWriter */
	//ReturnCode_t delete_contained_entities();

	///* JDXCZ    设置DataWriterQos的默认值 */
	//ReturnCode_t set_default_datawriter_qos(const DataWriterQos& Qos);

	/* JDXCZ    获取DataWriterQos的默认值 */
	ReturnCode_t get_default_datawriter_qos(DataWriterQos& Qos);

	///* JDXCZ 将TopicQos的值复制到DataWriterQos */
	//ReturnCode_t copy_from_topic_qos(DataWriterQos& datawriter_qos, const TopicQos& topic_qos);

	///* JDXCZ 设置PubliserQos的值，不兼容则设置失败 */
	//ReturnCode_t set_qos(const PublisherQos& QoS);

	/* JDXCZ 获取PublisherQos的值 */
	ReturnCode_t get_qos(PublisherQos& QoS);

	///* JDXCZ 设置PublisherListener的值 */
	//ReturnCode_t set_listener(PublisherListener* pListener, StatusMask mask);

	///* JDXCZ 获取PublisherListener的值 */
	//PublisherListener* get_listener();

public:
	PublisherImpl* getImpl();

private:
	PublisherImpl* m_pPublisherImpl;
};
#endif
