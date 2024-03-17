/************************************************************
** 文件名：Topic.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-15
** 修改人：无
** 日  期：无
** 描  述：Topic头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_TOPIC_H_INCLUDED_
#define _DDS_TOPIC_H_INCLUDED_

/* Nephalem 用户头文件 */
#include "ReturnCode.h"
#include "BasicTypes.h"
#include "DDS/TopicDescription.h"
#include "QoSPolicy.h"
/* Nephalem 系统头文件 */

/* Nephalem 前置声明 */
class DomainParticipant;
class TopicListener;
class TopicImpl;
class DDS_DLL Topic : public TopicDescription
{
public:
	/* Nephalem 构造函数 */
	Topic(TopicImpl* pTopicImpl);

	/* Nephalem 析构函数 */
	~Topic();

public:
	/* Nephalem 以下为规范中定义的接口 */

	/* Nephalem 检索主题状态 */
	//ReturnCode_t get_inconsistent_topic_status(InconsistentTopicStatus status);

	/* Nephalem 设置监听器 */
	//ReturnCode_t set_listener(TopicListener* pTopicListener, StatusMask mask);

	///* Nephalem 获取设置的监听器 */
	//TopicListener* get_listener();

	///* Nephalem 设置默认的TopicQos，不兼容则设置失败 */
	//ReturnCode_t set_qos(const TopicQos& QoS);

	/* Nephalem 获取TopicQos默认值 */
	ReturnCode_t get_qos(TopicQos& QoS);

private:
	TopicImpl* m_pTopicImpl;	
};

#endif
