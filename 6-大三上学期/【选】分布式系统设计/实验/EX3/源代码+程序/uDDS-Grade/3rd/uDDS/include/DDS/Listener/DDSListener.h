/************************************************************
** �ļ�����DDSListener.h
** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
** �����ˣ�Nephalem<250610346@qq.com>
** ��  �ڣ�2011-01-20
** �޸��ˣ���
** ��  �ڣ���
** ��  ����DDSListenerͷ�ļ�
** ��  ����Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_LISTENER_H_INCLUDED_
#define _DDS_LISTENER_H_INCLUDED_

#include "QoSPolicy.h"
#include "SEQ/Sequence.h"

struct QosPolicyCount
{
	QosPolicyId_t 	policy_id;
	int				count;
};

typedef  sequence<QosPolicyCount>  QosPolicyCountSeq;

class DDS_DLL DDSListener
{
public:
    DDSListener() {};

    virtual ~DDSListener() {};
};

#endif
