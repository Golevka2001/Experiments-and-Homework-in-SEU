/************************************************************
** �ļ�����Publisher.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Publisherͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _Publisher_H_
#define _Publisher_H_

/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "QoSPolicy.h"

/* Nephalem ϵͳͷ�ļ� */

/* Nephalem ǰ������ */
class PublisherImpl;
class DataWriterListener;

class DDS_DLL Publisher
{
public:
	//���캯��
	Publisher(PublisherImpl* pPublisherImpl);
	//��������
	virtual ~Publisher(void);
public:
	/* JDXCZ �˴�Ϊ�淶�ж���Ľӿ� */

	/* JDXCZ ��������д�� */
	DataWriter* create_datawriter(Topic* pTopic, const DataWriterQos& Qos, DataWriterListener * pDataWriterListener, StatusMask mask);

	/* JDXCZ ɾ������д�� */
	ReturnCode_t delete_datawriter(DataWriter* pDataWriter);

	/* JDXCZ ��������д�� */
	_DATA_WRITER_LIST_T  lookup_datawriter(const string& topic_name);

	///* JDXCZ ����DDS����Ӧ�ý������ڱ�Publisher��DataWriter������ж���޸� */
	//ReturnCode_t suspend_publications();

	///* JDXCZ	��֪����Ӧ�ó��������֮ǰsuspend_publications���������Ķ���޸ģ�
	//			����ʵ���߿���ʹ��������ʾ����������suspend_publications���������������޸�*/
	//ReturnCode_t resume_pulications();

	///* JDXCZ Ҫ��Ӧ�ó���ʹ������Publisher��DataWriter����ʼ��һ�¼������޸� */
	//ReturnCode_t begin_coherent_changes();

	///* JDXCZ �ս���begin_coherent_changes�����������ġ�һ�¼��� */
	//ReturnCode_t end_coherent_changes();

	///* JDXCZ	���������̣߳�ֱ������ƥ��Ŀɿ���DataReaderʵ�嶼ȷ���յ��ɿ���DataWriterʵ��д�����������
	//			����max_wait�����趨�ĳ���ʱ���Ѿ����� */
	//ReturnCode_t wait_for_acknowledgments(Duration_t max_wait);

	/* JDXCZ    ����Publisher������Domainparticipant */
	DomainParticipant* get_participant();

	///* JDXCZ    ɾ��Publisher���󴴽�������ʵ�壬ɾ�����а�����DataWriter */
	//ReturnCode_t delete_contained_entities();

	///* JDXCZ    ����DataWriterQos��Ĭ��ֵ */
	//ReturnCode_t set_default_datawriter_qos(const DataWriterQos& Qos);

	/* JDXCZ    ��ȡDataWriterQos��Ĭ��ֵ */
	ReturnCode_t get_default_datawriter_qos(DataWriterQos& Qos);

	///* JDXCZ ��TopicQos��ֵ���Ƶ�DataWriterQos */
	//ReturnCode_t copy_from_topic_qos(DataWriterQos& datawriter_qos, const TopicQos& topic_qos);

	///* JDXCZ ����PubliserQos��ֵ��������������ʧ�� */
	//ReturnCode_t set_qos(const PublisherQos& QoS);

	/* JDXCZ ��ȡPublisherQos��ֵ */
	ReturnCode_t get_qos(PublisherQos& QoS);

	///* JDXCZ ����PublisherListener��ֵ */
	//ReturnCode_t set_listener(PublisherListener* pListener, StatusMask mask);

	///* JDXCZ ��ȡPublisherListener��ֵ */
	//PublisherListener* get_listener();

public:
	PublisherImpl* getImpl();

private:
	PublisherImpl* m_pPublisherImpl;
};
#endif
