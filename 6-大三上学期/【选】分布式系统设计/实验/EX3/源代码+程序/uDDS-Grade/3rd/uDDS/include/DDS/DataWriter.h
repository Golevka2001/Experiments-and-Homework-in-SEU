/************************************************************
** �ļ�����DataWriter.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-04-21
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DataWriterͷ�ļ�
** ��  ����Version 0.1
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


/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"
#include "DDS/Listener/DataWriterListener.h"
/* Nephalem ϵͳͷ�ļ� */

/* Nephalem ǰ������ */
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
	//���캯��
	DataWriter(DataWriterImpl* pDataWriterImpl);

	virtual ~DataWriter();
public:
	/* JDXCZ �˴�Ϊ�淶�ж���Ľӿ� */

	/* JDXCZ    ֪ͨ����Ӧ�ó����޸��ض�����ʵ�� */
	//virtual InstanceHandle_t register_instance(const Data* instance);

	///* JDXCZ    ֪ͨ����Ӧ�ó����޸��ض�����ʵ�������޸�source_timestamp��ֵ */
	//InstanceHandle_t register_instance_w_timestamp(const Data* instance, const Time_t& timestamp);

	///* JDXCZ    ����OFFERED_DEADLINE_MISSEDͨ��״̬ */
	//ReturnCode_t unregister_instance(const Data* instance, const InstanceHandle_t& handle);

	///* JDXCZ    ����OFFERED_DEADLINE_MISSEDͨ��״̬ */
	//ReturnCode_t  unregister_instance_w_timestamp(const Data* instance, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    ȡ��instance_handle��Ӧ��ʵ���ؼ���ֵ */
	//ReturnCode_t get_key_value(const Data* key_holder, const InstanceHandle_t& handle);

	///* JDXCZ    ����DataWriterʵ�� */
	//InstanceHandle_t lookup_instance(const Data* instance);

	/* JDXCZ    �޸�����ʵ����ֵ ������������Dataδȷ����Data ���͸�Ϊchar* */
	//ReturnCode_t write(const Data* data, const InstanceHandle_t& handle);

	/* Nephalem ����Ϸ�write�ӿڣ����ཫ����ת��Ϊchar*�� ���� */
	ReturnCode_t write(const char* pData,unsigned int length, const InstanceHandle_t& handle);

	///* JDXCZ    �޸�����ʵ����ֵ��ͨ��SampleInfo��source_timestamp�����ṩ�ɹ�DataReader����ʹ�õ�source_timestamp��ֵ */
	//ReturnCode_t write_w_timestamp(const Data* data, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    �����м��ɾ�����ݣ�ͨ��SampleInfo��source_timestamp�����ṩ�ɹ�DataReader����ʹ�õ�source_timestamp��ֵ��*/
	//ReturnCode_t dispose(const Data* data, const InstanceHandle_t& handle);

	///* JDXCZ    �����м��ɾ������ ������*/
	//ReturnCode_t dispose_w_timestamp(const Data* data, const InstanceHandle_t& handle, const Time_t& timestamp);

	///* JDXCZ    ���������̣߳�֪��DataWriter���͵����ݱ�����RELIABLE��DataReaderʵ��ȷ�� */
	//ReturnCode_t wait_for_acknowledgments(const Duration_t& max_wait);

	/* JDXCZ    ����LIVELINESS_LOSTͨ��״̬*/
	//ReturnCode_t get_liveliness_lost_status(LivelinessLostStatus& status);

	///* JDXCZ    ����OFFERED_DEADLINE_MISSEDͨ��״̬ */
	//ReturnCode_t get_offered_deadline_missed_status(_OFFERED_DEADLINE_MISSED_STATUS& status);

	///* JDXCZ    ����OFFERED_INCOMPATIBLE_QOSͨ��״̬ */
	//ReturnCode_t get_offered_incompatible_qos_status(_OFFERED_DEADLINE_MISSED_STATUS& status);

	/* JDXCZ    ����Publication_matched��ͨ��״̬ */
	//ReturnCode_t get_publication_matched_status(PublicationMatchedStatus& status);

	/* JDXCZ    ����DataWriter���������� */
	Topic* get_topic();

	/* JDXCZ    ��ȡDataWriter������Publisher */
	Publisher* get_publisher();

	///* JDXCZ    ����DataWriter�Ļ�Ծ�� */
	//ReturnCode_t assert_liveliness();

	///* JDXCZ    ��ȡ��ǰ��DataWriter ���������Ķ����б���Ϣ */
	//ReturnCode_t get_matched_subscription_data(SubscriptionBuiltinTopicData& subscription_data);

	/* JDXCZ    ��ȡ��ǰ��DataWriter ���������Ķ����б� */
	//ReturnCode_t get_matched_subscriptions(InstanceHandle_t& subscription_handles[]);

	//	/* JDXCZ ����PubliserQos��ֵ��������������ʧ�� */
	//ReturnCode_t set_qos(const DataWriterQos& QoS);

	/* JDXCZ ��ȡPublisherQos��ֵ */
	ReturnCode_t get_qos(DataWriterQos& QoS);

	///* JDXCZ ����PublisherListener��ֵ */
	//ReturnCode_t set_listener(DataWriterListener* pListener, StatusMask mask);

	///* JDXCZ ��ȡPublisherListener��ֵ */
	//DataWriterListener* get_listener();

public:
	DataWriterImpl* getImpl();

	/* Nephalem ��ȡ�����Guid */
	GUID_t getGuid();

private:
	DataWriterImpl* m_pDataWriterImpl;
};

#endif
