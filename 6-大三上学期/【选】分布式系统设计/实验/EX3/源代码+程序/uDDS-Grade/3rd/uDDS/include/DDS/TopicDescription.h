/************************************************************
** 文件名：TopicDescription.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：徐晓希
** 日  期：2010-01-18
** 描  述：TopicDescription头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPICDESCRIPTION_H_INCLUDED_
#define _DDS_TOPICDESCRIPTION_H_INCLUDED_

/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"

/* Nephalem 系统头文件 */

/* Nephalem 前置声明 */
class TopicDescriptionImpl;


class DDS_DLL TopicDescription
{
public:
	TopicDescription(TopicDescriptionImpl* pTopicDescriptionImpl);
	virtual ~TopicDescription() {};

public:
	/* Nephalem 以下为规范中定义的接口 */

	/* Nephale 获取相关的DomainParticipant*/
	DomainParticipant* get_participant();

	/* Nephalem 获取类型名 */
	virtual string get_type_name();

	/* Nephalem 获取主题名 */
	virtual string get_name();

public:
	TopicDescriptionImpl* getImpl();

private:

	TopicDescriptionImpl* m_pTopicDescriptionImpl;
	

};

#endif
