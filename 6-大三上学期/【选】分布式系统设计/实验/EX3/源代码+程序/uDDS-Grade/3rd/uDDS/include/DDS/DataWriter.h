/************************************************************
** 文件名：DataWriter.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-04-21
** 修改人：无
** 日  期：无
** 描  述：DataWriter头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAWRITER_H_INCLUDED_
#define _DDS_DATAWRITER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"

class DataWriterListener;
class Writer;
class Publisher;
class Topic;
class HistoryCache;
class DomainEntity;
class Discovery;
class DomainParticipant;


/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"
#include "DDS/Listener/DataWriterListener.h"
/* Nephalem 系统头文件 */

/* Nephalem 前置声明 */
class DomainParticipantListener;
class Publisher;
class PublisherListener;
class Subscriber;
class SubscriberListener;
class TopicListener;
class MultiTopic;
class DomainParticipantImpl;
class DomainEntity;
class DataWriterImpl;
typedef  void Data;

class DDS_DLL DataWriter 
{
public:
	//构造函数
	DataWriter(DataWriterImpl* pDataWriterImpl);

	virtual ~DataWriter();
public:
	/* JDXCZ 此处为规范中定义的接口 */

	/* JDXCZ    通知服务应用程序将修改特定数据实例 */
	//virtual InstanceHandle_t register_instance(const Data* instance);

	///* JDXCZ    通知服务应用程序将修改特定数据实例，并修改source_timestamp的值 */
	//InstanceHandle_t register_instance_w_timestamp(const Data* instance, const Time_t& timestamp);

	///* JDXCZ    访问OFFERED_DEADLINE_MISSED通信状态 */
	//ReturnCode_t unregister_instance(const Data* instance, const InstanceHandle_t& handle);

	///* JDXCZ    访问OFFERED_DEADLINE_MISSED通信状态 */
	//ReturnCode_t  unregister_instance_w_timestamp(const Data* instance, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    取与instance_handle对应的实例关键字值 */
	//ReturnCode_t get_key_value(const Data* key_holder, const InstanceHandle_t& handle);

	///* JDXCZ    返回DataWriter实例 */
	//InstanceHandle_t lookup_instance(const Data* instance);

	/* JDXCZ    修改数据实例的值 由于数据类型Data未确定，Data 类型改为char* */
	//ReturnCode_t write(const Data* data, const InstanceHandle_t& handle);

	/* Nephalem 替代上方write接口，子类将数据转化为char*后 传入 */
	ReturnCode_t write(const char* pData,unsigned int length, const InstanceHandle_t& handle);

	///* JDXCZ    修改数据实例的值，通过SampleInfo中source_timestamp属性提供可供DataReader对象使用的source_timestamp的值 */
	//ReturnCode_t write_w_timestamp(const Data* data, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    请求中间价删除数据，通过SampleInfo中source_timestamp属性提供可供DataReader对象使用的source_timestamp的值。*/
	//ReturnCode_t dispose(const Data* data, const InstanceHandle_t& handle);

	///* JDXCZ    请求中间价删除数据 ，设置*/
	//ReturnCode_t dispose_w_timestamp(const Data* data, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    阻塞调用线程，知道DataWriter发送的数据被所有RELIABLE的DataReader实体确认 */
	//ReturnCode_t wait_for_acknowledgments(const Duration_t& max_wait);

	/* JDXCZ    访问LIVELINESS_LOST通信状态*/
	//ReturnCode_t get_liveliness_lost_status(LivelinessLostStatus& status);

	///* JDXCZ    访问OFFERED_DEADLINE_MISSED通信状态 */
	//ReturnCode_t get_offered_deadline_missed_status(_OFFERED_DEADLINE_MISSED_STATUS& status);

	///* JDXCZ    访问OFFERED_INCOMPATIBLE_QOS通信状态 */
	//ReturnCode_t get_offered_incompatible_qos_status(_OFFERED_DEADLINE_MISSED_STATUS& status);

	/* JDXCZ    访问Publication_matched的通信状态 */
	//ReturnCode_t get_publication_matched_status(PublicationMatchedStatus& status);

	/* JDXCZ    返回DataWriter关联的主题 */
	Topic* get_topic();

	/* JDXCZ    获取DataWriter所属的Publisher */
	Publisher* get_publisher();

	///* JDXCZ    断言DataWriter的活跃性 */
	//ReturnCode_t assert_liveliness();

	///* JDXCZ    获取当前与DataWriter “关联”的订阅列表信息 */
	//ReturnCode_t get_matched_subscription_data(SubscriptionBuiltinTopicData& subscription_data);

	/* JDXCZ    获取当前与DataWriter “关联”的订阅列表 */
	//ReturnCode_t get_matched_subscriptions(InstanceHandle_t& subscription_handles[]);

	//	/* JDXCZ 设置PubliserQos的值，不兼容则设置失败 */
	//ReturnCode_t set_qos(const DataWriterQos& QoS);

	/* JDXCZ 获取PublisherQos的值 */
	ReturnCode_t get_qos(DataWriterQos& QoS);

	///* JDXCZ 设置PublisherListener的值 */
	//ReturnCode_t set_listener(DataWriterListener* pListener, StatusMask mask);

	///* JDXCZ 获取PublisherListener的值 */
	//DataWriterListener* get_listener();

public:
	DataWriterImpl* getImpl();

	/* Nephalem 获取自身的Guid */
	GUID_t getGuid();

private:
	DataWriterImpl* m_pDataWriterImpl;
};

#endif
