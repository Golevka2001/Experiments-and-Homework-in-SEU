/************************************************************
** 文件名：subscriber.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：subscriber头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _Subscriber_H_
#define _Subscriber_H_

/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"

/* Nephalem 系统头文件 */
#include "DDS/TopicDescription.h"

/* Nephalem 前置声明 */
class DataReaderListener;
class SubscriberListener;

class DDS_DLL Subscriber
{
public:
	//构造函数
	Subscriber(SubscriberImpl* pSubscriberImpl);
	//析构函数
	virtual ~Subscriber(void);
public:
	/* JDXCZ 此处为规范中定义的接口 */

	/* JDXCZ 设置SubscriberQos的值，不兼容则设置失败 */
	ReturnCode_t set_qos(const SubscriberQos& QoS);

	/* JDXCZ 获取SubscriberQos的值 */
	ReturnCode_t get_qos(SubscriberQos& QoS);

	/* JDXCZ 设置SubscriberListener的值 */
	ReturnCode_t set_listener(SubscriberListener* pListener, StatusMask mask);

	/* JDXCZ 获取SubscriberListener的值 */
	SubscriberListener* get_listener();

	/* JDXCZ    创建数据写者 */
	DataReader* create_datareader(TopicDescription* pTopic, const DataReaderQos& Qos,  DataReaderListener* pDataReaderListener, StatusMask mask);

	/* JDXCZ    删除数据读者 */
	ReturnCode_t delete_datareader(DataReader* pDataReader);

	/* JDXCZ   查找数据读者 */
	DataReader* lookup_datareader(const string& topic_name);

	///* JDXCZ   表示应用程序即将访问附加到订阅者（Subscriber）上的任何DataReader对象中的数据样本 */
	//ReturnCode_t begin_access();

	///* JDXCZ   此方法表示应用程序已完成访问Subscriber管理的DataReader对象中的数据样本 */
	//ReturnCode_t end_access();

	///* JDXCZ   此方法允许应用程序访问包含具有指定sample_states，view_states和instance_states的样本的DataReader对象 */
	//ReturnCode_t get_datareaders(DataReader* pDataReaders[], const SampleStateKind& sample_states[], const ViewStateKind& view_states[], const InstanceStateKind& instanceStateKind[]);

	///* JDXCZ 此方法调用绑定到DataReader实体的DataReaderListener对象的on_data_available方法，该实体的DATA_AVAILABLE状态被视为已更改。
	//	通常在SubscriberListener的on_data_on_readers方法中调用此方法。这样一来SubscriberListener可以委托DataReaderListener对象处理数据 */
	//ReturnCode_t notify_datareaders();

	///* JDXCZ 允许访问SAMPLE_LOST通信状态   */
	///* ReturnCode_t  get_sample_lost_status( SampleLostStatus& status); */

	/* JDXCZ 获取Subscriber所属的DomainParticipant */
	DomainParticipant* get_participant();

	///* JDXCZ 删除Subscriber中所有实体，删除所有DataReader */
	//ReturnCode_t delete_contained_entities();

	///* JDXCZ 设置DataReader的默认Qos */
	//ReturnCode_t set_default_datareader_qos(const DataReaderQos& Qos);

	/* JDXCZ 获取DataReader的默认Qos */
	ReturnCode_t get_default_datareader_qos(DataReaderQos& Qos);

	///* JDXCZ 将TopicQos的值复制到DataReaderQos */
	//ReturnCode_t copy_from_topic_qos(DataReaderQos& datareader_qos, const TopicQos& topic_qos);

public:
	SubscriberImpl* getImpl();

private:
	SubscriberImpl* m_pSubscriberImpl;
};
#endif
