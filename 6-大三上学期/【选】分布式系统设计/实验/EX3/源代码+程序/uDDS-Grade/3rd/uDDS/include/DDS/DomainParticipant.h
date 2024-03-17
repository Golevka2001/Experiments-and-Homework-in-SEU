/************************************************************
** �ļ�����DomainParticipant.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-03-05
** ��  ����DomainParticipantͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/

#ifndef _DDS_DOMAIN_PARTICIPANT_H_
#define _DDS_DOMAIN_PARTICIPANT_H_

/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"

/* Nephalem ϵͳͷ�ļ� */
#include <list>
using std::list;

/* Nephalem ǰ������ */
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
	/* Nephalem ���캯�� */
	DomainParticipant(DomainParticipantImpl* m_pDomainParticipantImpl);

	/*Nephalem �������� */
	~DomainParticipant();
public:
	/* Nephalem �˴�Ϊ�淶�ж���Ľӿ� */

	/* Nephalem ������������ */
	Publisher* create_publisher(const PublisherQos& QoS, PublisherListener * pPublisherListener, StatusMask mask);

	/* Nephalem ɾ��������*/
	ReturnCode_t delete_publisher(Publisher*& pPublisher);

	/* Nephalem ���������� */
	Subscriber* create_subscriber(const SubscriberQos& QoS, SubscriberListener* pSubscriberListener, StatusMask mask);

	/* Nephalem ɾ�������� */
	ReturnCode_t delete_subscriber(Subscriber*& pSubscriber);

	/* Nephalem ����Topic */
	Topic* create_topic(const string& topicName, const string& typeName, const TopicQos& QoS, TopicListener * pTopicListener, StatusMask mask);

	/* Nephalem ɾ��ָ�����⣬��������⻹�ڱ�DataWriter��DataReader��ʹ�ã���ɾ��ʧ�� */
	ReturnCode_t delete_topic(Topic*& pTopic);

	/* Nephalem �����������ݹ��˵����� */
	ContentFilteredTopic* create_contentfilteredtopic(const string& name, Topic* pRelatedTopic, const string& filterExpression, const StringSeq& expressionParameters);

	/* Nephalem ɾ���������ݹ��˵����� */
	ReturnCode_t delete_contentfilteredtopic(const ContentFilteredTopic*& pContentFilteredTopic);

	/* Nephalem ������������ */
	MultiTopic* create_multitopic(const string& topicName, const string& typeName, const string& subscriptionExpression, const StringSeq& expressionParameters);

	/* Nephalem ɾ���������� */
	ReturnCode_t delete_multitopic(const MultiTopic*& pMultiTopic);

	/* Nephalem ���ü����� */
	ReturnCode_t set_listener(DomainParticipantListener* pDomainParticipantListener, StatusMask mask);

	/* Nephalem ������������������ */
	Topic* find_topic(const string& topicName, Duration_t timeout);

	/* Nephalem �����������ڱ��ز������� */
	TopicDescription* lookup_topicdescription(const string& topicName);

	/* Nephalem ��ȡ���ö����� */
	Subscriber* get_builtin_subscriber();

	/* Nephalem ����Զ�˲����� */
	ReturnCode_t ignore_participant(InstanceHandle_t handle);

	/* Nephalem ����Զ������ */
	ReturnCode_t ignore_topic(InstanceHandle_t handle);

	/* Nephalem ����Զ�˷����� */
	ReturnCode_t ignore_publication(InstanceHandle_t handle);

	/* Nephalem ����Զ�˶����� */
	ReturnCode_t ignore_subscription(InstanceHandle_t handle);

	/* Nephalem ��ȡ�����ڵ��� */
	_DOMAINID_T get_domain_id();

	/* Nephalem ɾ���û�����������ʵ����� */
	ReturnCode_t delete_contained_entities();

	/* Nephalem �ֶ����Դ���� */
	ReturnCode_t assert_liveliness();

	/* Nephalem ����Ĭ�ϵķ�����QoS */
	ReturnCode_t set_default_publisher_qos(const PublisherQos& QoS);

	/* Nephalem ��ȡĬ�ϵķ�����QoS */
	ReturnCode_t get_default_publisher_qos(PublisherQos& QoS);

	/* Nephalem ����Ĭ�ϵĶ�����QoS */
	ReturnCode_t set_default_subscriber_qos(const SubscriberQos& QoS);

	/* Nephalem ��ȡĬ�ϵĶ�����QoS */
	ReturnCode_t get_default_subscriber_qos(SubscriberQos& QoS);

	/* Nephalem ����Ĭ�ϵ�����QoS */
	ReturnCode_t set_default_topic_qos(const TopicQos& QoS);

	/* Nephalem ��ȡĬ�ϵ�����QoS */
	ReturnCode_t get_default_topic_qos(TopicQos& QoS);

	/* Nephalem ��ȡ�ѷ��ֵ�Զ��DomainParticipant�б� */
	ReturnCode_t get_discovered_participants(InstanceHandleSeq& participantHandles);

	/* Nephalem ��ȡָ��Զ��DomainParticipant������ */
	ReturnCode_t get_discovered_participant_data(ParticipantBuiltinTopicData& participantData, const InstanceHandle_t& participantHandle);

	///* Nephalem ��ȡ�ѷ��ֵ�Զ�������б� */
	//ReturnCode_t get_discovered_topics(vector<InstanceHandle_t>& topicHandles);

	///* Nephalem ��ȡָ����������� */
	////ReturnCode_t get_discovered_topic_data(TopicBuiltinTopicData& topicData, const InstanceHandle_t& topicHandle);

	/* Nephalem �ж�ʵ���Ƿ��ɸ�DomainParticipant���� */
	bool contains_entity(const InstanceHandle_t& handle);

	/* Nephalem ��ȡ��ǰʱ�� */
	static ReturnCode_t get_current_time(Time_t& currentTime);

	///* Nephalem ��ȡ���õļ����� */
	//DomainParticipantListener* get_listener();

	///* Nephalem ����Ĭ�ϵ�DomainParticipantQos��������������ʧ�� */
	//ReturnCode_t set_qos(const DomainParticipantQos& QoS);

	/* Nephalem ��ȡDomainParticipantQosĬ��ֵ */
	ReturnCode_t get_qos(DomainParticipantQos& QoS);

public:
	/* Nephalem �û�����ӿ� */
	DomainParticipantImpl* getImpl();

	/* Nephalem ע���������� */
	ReturnCode_t register_type(const string & typeName);

	/* Nephalem ��ȡ�ѷ��ֵ�DataWriter�б� */
	ReturnCode_t get_publications(InstanceHandleSeq& publication_handles, bool include_contained_entities);

	/* Nephalem ��ȡָ����DataWriter��Ϣ */
	ReturnCode_t get_publication_data(struct PublicationBuiltinTopicData& publication_data, const InstanceHandle_t& publication_handle);

	/* Nephalem ��ȡ�ѷ��ֵ�DataReader�б� */
	ReturnCode_t get_subscriptions(InstanceHandleSeq& subscription_handles,bool include_contained_entities);

	/* Nephalem ��ȡָ����DataReader��Ϣ */
	ReturnCode_t get_subscription_data(struct SubscriptionBuiltinTopicData& subscription_data,const InstanceHandle_t& subscription_handle);

	/* Nephalem ���ü�ش�������� */
	ReturnCode_t set_monitor_listener(DomainParticipantListener* pMonitorListener, StatusMask mask);

private:
	DomainParticipantImpl* m_pDomainParticipantImpl;
};

#endif

