/************************************************************
** 文件名：DDSListener.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-20
** 修改人：无
** 日  期：无
** 描  述：DDSListener头文件
** 版  本：Version 0.1
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
