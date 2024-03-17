/************************************************************
** 文件名：DomainParticipant.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：Nephalem<250610346@qq.com>
** 日  期：2011-03-05
** 描  述：DomainParticipant头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_DOMAIN_PARTICIPANT_H_
#define _DDS_DOMAIN_PARTICIPANT_H_

/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"

/* Nephalem 系统头文件 */
#include <list>
using std::list;

/* Nephalem 前置声明 */
class DomainParticipantListener;
class Publisher;
class PublisherListener;
class Subscriber;
class SubscriberListener;
class TopicListener;
class MultiTopic;
class DomainParticipantImpl;

class DDS_DLL DomainParticipant
{
public:
	/* Nephalem 构造函数 */
	DomainParticipant(DomainParticipantImpl* m_pDomainParticipantImpl);

	/*Nephalem 析构函数 */
	~DomainParticipant();
public:
	/* Nephalem 此处为规范中定义的接口 */

	/* Nephalem 创建发布者者 */
	Publisher* create_publisher(const PublisherQos& QoS, PublisherListener * pPublisherListener, StatusMask mask);

	/* Nephalem 删除发布者*/
	ReturnCode_t delete_publisher(Publisher*& pPublisher);

	/* Nephalem 创建订阅者 */
	Subscriber* create_subscriber(const SubscriberQos& QoS, SubscriberListener* pSubscriberListener, StatusMask mask);

	/* Nephalem 删除订阅者 */
	ReturnCode_t delete_subscriber(Subscriber*& pSubscriber);

	/* Nephalem 创建Topic */
	Topic* create_topic(const string& topicName, const string& typeName, const TopicQos& QoS, TopicListener * pTopicListener, StatusMask mask);

	/* Nephalem 删除指定主题，如果该主题还在被DataWriter、DataReader等使用，则删除失败 */
	ReturnCode_t delete_topic(Topic*& pTopic);

	/* Nephalem 创建基于内容过滤的主题 */
	ContentFilteredTopic* create_contentfilteredtopic(const string& name, Topic* pRelatedTopic, const string& filterExpression, const StringSeq& expressionParameters);

	/* Nephalem 删除基于内容过滤的主题 */
	ReturnCode_t delete_contentfilteredtopic(const ContentFilteredTopic*& pContentFilteredTopic);

	/* Nephalem 创建复数主题 */
	MultiTopic* create_multitopic(const string& topicName, const string& typeName, const string& subscriptionExpression, const StringSeq& expressionParameters);

	/* Nephalem 删除复数主题 */
	ReturnCode_t delete_multitopic(const MultiTopic*& pMultiTopic);

	/* Nephalem 设置监听器 */
	ReturnCode_t set_listener(DomainParticipantListener* pDomainParticipantListener, StatusMask mask);

	/* Nephalem 根据主题名查找主题 */
	Topic* find_topic(const string& topicName, Duration_t timeout);

	/* Nephalem 根据主题名在本地查找主题 */
	TopicDescription* lookup_topicdescription(const string& topicName);

	/* Nephalem 获取内置订阅者 */
	Subscriber* get_builtin_subscriber();

	/* Nephalem 忽略远端参与者 */
	ReturnCode_t ignore_participant(InstanceHandle_t handle);

	/* Nephalem 忽略远端主题 */
	ReturnCode_t ignore_topic(InstanceHandle_t handle);

	/* Nephalem 忽略远端发布者 */
	ReturnCode_t ignore_publication(InstanceHandle_t handle);

	/* Nephalem 忽略远端订阅者 */
	ReturnCode_t ignore_subscription(InstanceHandle_t handle);

	/* Nephalem 获取所属于的域 */
	_DOMAINID_T get_domain_id();

	/* Nephalem 删除用户创建的所有实体对象 */
	ReturnCode_t delete_contained_entities();

	/* Nephalem 手动断言存活性 */
	ReturnCode_t assert_liveliness();

	/* Nephalem 设置默认的发布者QoS */
	ReturnCode_t set_default_publisher_qos(const PublisherQos& QoS);

	/* Nephalem 获取默认的发布者QoS */
	ReturnCode_t get_default_publisher_qos(PublisherQos& QoS);

	/* Nephalem 设置默认的订阅者QoS */
	ReturnCode_t set_default_subscriber_qos(const SubscriberQos& QoS);

	/* Nephalem 获取默认的订阅者QoS */
	ReturnCode_t get_default_subscriber_qos(SubscriberQos& QoS);

	/* Nephalem 设置默认的主题QoS */
	ReturnCode_t set_default_topic_qos(const TopicQos& QoS);

	/* Nephalem 获取默认的主题QoS */
	ReturnCode_t get_default_topic_qos(TopicQos& QoS);

	/* Nephalem 获取已发现的远端DomainParticipant列表 */
	ReturnCode_t get_discovered_participants(InstanceHandleSeq& participantHandles);

	/* Nephalem 获取指定远端DomainParticipant的数据 */
	ReturnCode_t get_discovered_participant_data(ParticipantBuiltinTopicData& participantData, const InstanceHandle_t& participantHandle);

	///* Nephalem 获取已发现的远端主题列表 */
	//ReturnCode_t get_discovered_topics(vector<InstanceHandle_t>& topicHandles);

	///* Nephalem 获取指定主题的数据 */
	////ReturnCode_t get_discovered_topic_data(TopicBuiltinTopicData& topicData, const InstanceHandle_t& topicHandle);

	/* Nephalem 判断实体是否由该DomainParticipant创建 */
	bool contains_entity(const InstanceHandle_t& handle);

	/* Nephalem 获取当前时间 */
	static ReturnCode_t get_current_time(Time_t& currentTime);

	///* Nephalem 获取设置的监听器 */
	//DomainParticipantListener* get_listener();

	///* Nephalem 设置默认的DomainParticipantQos，不兼容则设置失败 */
	//ReturnCode_t set_qos(const DomainParticipantQos& QoS);

	/* Nephalem 获取DomainParticipantQos默认值 */
	ReturnCode_t get_qos(DomainParticipantQos& QoS);

public:
	/* Nephalem 用户定义接口 */
	DomainParticipantImpl* getImpl();

	/* Nephalem 注册数据类型 */
	ReturnCode_t register_type(const string & typeName);

	/* Nephalem 获取已发现的DataWriter列表 */
	ReturnCode_t get_publications(InstanceHandleSeq& publication_handles, bool include_contained_entities);

	/* Nephalem 获取指定的DataWriter信息 */
	ReturnCode_t get_publication_data(struct PublicationBuiltinTopicData& publication_data, const InstanceHandle_t& publication_handle);

	/* Nephalem 获取已发现的DataReader列表 */
	ReturnCode_t get_subscriptions(InstanceHandleSeq& subscription_handles,bool include_contained_entities);

	/* Nephalem 获取指定的DataReader信息 */
	ReturnCode_t get_subscription_data(struct SubscriptionBuiltinTopicData& subscription_data,const InstanceHandle_t& subscription_handle);

	/* Nephalem 设置监控代理监听器 */
	ReturnCode_t set_monitor_listener(DomainParticipantListener* pMonitorListener, StatusMask mask);

private:
	DomainParticipantImpl* m_pDomainParticipantImpl;
};

#endif

