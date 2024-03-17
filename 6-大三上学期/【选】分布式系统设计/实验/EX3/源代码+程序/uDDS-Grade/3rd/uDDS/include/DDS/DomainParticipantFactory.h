/************************************************************
** �ļ�����DomainParticipantFactory.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-17
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DomainParticipantFactoryͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_
#define _DDS_DOMAINPARTICIPANTFACTORY_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"

#include "DDS/DomainParticipant.h"
#include "Listener/DomainParticipantListener.h"

class DomainParticipantFactoryImpl;
class DDS_DLL DomainParticipantFactory
{
public:
	~DomainParticipantFactory();
	/* Nephalem ����Ϊ�淶�ж���Ľӿ� */
	/* Nephalem ����DomainParticipant���� */
	 DomainParticipant* create_participant(_DOMAINID_T DomainId,
		const DomainParticipantQos& QoS, 
		DomainParticipantListener* pDomainParticipantListener,
		StatusMask mask);

	/* Nephalem ɾ��������� */
	 ReturnCode_t delete_participant(DomainParticipant* & pDomainParticipant);

	/* Nephalem �淶�ж���Ϊ�������һ��DomainParticipant���˴������̰߳�ȫ���� */
	 DomainParticipant* lookup_participant(_DOMAINID_T DomainId);

	/* Nephalem ����Ĭ�ϵ�DomainParticipantQoS��������������ʧ�� */
	 ReturnCode_t set_default_participant_qos(const DomainParticipantQos& QoS);

	/* Nephalem ��ȡDomainParticipantQoSĬ��ֵ */
	 ReturnCode_t get_default_participant_qos(DomainParticipantQos& QoS);

	/* Nephalem ����Ĭ�ϵ�DomainParticipantFactoryQos��������������ʧ�� */
	 ReturnCode_t set_qos(const DomainParticipantFactoryQos& QoS);

	/* Nephalem ��ȡDomainParticipantFactoryQosĬ��ֵ */
	 ReturnCode_t get_qos(DomainParticipantFactoryQos& QoS);

	/* Nephalem ����ģʽ */
	static DomainParticipantFactory* get_instance();
	
private:

	/* Nephalem �������ⲿ�������� */
	DomainParticipantFactory();

	static DomainParticipantFactory* m_pDomainParticipantFactoryInstance;

	 DomainParticipantFactoryImpl* m_pDomainParticipantFactoryImpl;
};

#endif
