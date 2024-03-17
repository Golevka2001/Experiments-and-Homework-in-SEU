/************************************************************
** �ļ�����Topic.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ���
** ��  �ڣ���
** ��  ����Topicͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPIC_H_INCLUDED_
#define _DDS_TOPIC_H_INCLUDED_

/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/TopicDescription.h"
#include "QoSPolicy.h"
/* Nephalem ϵͳͷ�ļ� */

/* Nephalem ǰ������ */
class DomainParticipant;
class TopicListener;
class TopicImpl;
class DDS_DLL Topic : public TopicDescription
{
public:
	/* Nephalem ���캯�� */
	Topic(TopicImpl* pTopicImpl);

	/* Nephalem �������� */
	~Topic();

public:
	/* Nephalem ����Ϊ�淶�ж���Ľӿ� */

	/* Nephalem ��������״̬ */
	//ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus status);

	/* Nephalem ���ü����� */
	//ReturnCode_t set_listener(TopicListener* pTopicListener, StatusMask mask);

	///* Nephalem ��ȡ���õļ����� */
	//TopicListener* get_listener();

	///* Nephalem ����Ĭ�ϵ�TopicQos��������������ʧ�� */
	//ReturnCode_t set_qos(const TopicQos& QoS);

	/* Nephalem ��ȡTopicQosĬ��ֵ */
	ReturnCode_t get_qos(TopicQos& QoS);

private:
	TopicImpl* m_pTopicImpl;	
};

#endif
