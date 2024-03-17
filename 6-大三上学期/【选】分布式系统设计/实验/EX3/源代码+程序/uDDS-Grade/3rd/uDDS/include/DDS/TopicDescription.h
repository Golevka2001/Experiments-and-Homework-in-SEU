/************************************************************
** �ļ�����TopicDescription.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-15
** �޸��ˣ�����ϣ
** ��  �ڣ�2010-01-18
** ��  ����TopicDescriptionͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPICDESCRIPTION_H_INCLUDED_
#define _DDS_TOPICDESCRIPTION_H_INCLUDED_

/* Nephalem �û�ͷ�ļ� */
#include "ReturnCode.h"
#include "BasicTypes.h"

/* Nephalem ϵͳͷ�ļ� */

/* Nephalem ǰ������ */
class TopicDescriptionImpl;


class DDS_DLL TopicDescription
{
public:
	TopicDescription(TopicDescriptionImpl* pTopicDescriptionImpl);
	virtual ~TopicDescription() {};

public:
	/* Nephalem ����Ϊ�淶�ж���Ľӿ� */

	/* Nephale ��ȡ��ص�DomainParticipant*/
	DomainParticipant* get_participant();

	/* Nephalem ��ȡ������ */
	virtual string get_type_name();

	/* Nephalem ��ȡ������ */
	virtual string get_name();

public:
	TopicDescriptionImpl* getImpl();

private:

	TopicDescriptionImpl* m_pTopicDescriptionImpl;
	

};

#endif
