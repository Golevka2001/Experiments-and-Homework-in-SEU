/************************************************************
** 文件名：DomainParticipantFactory.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-17
** 修改人：无
** 日  期：无
** 描  述：DomainParticipantFactory头文件
** 版  本：Version 0.1
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
	/* Nephalem 以下为规范中定义的接口 */
	/* Nephalem 创建DomainParticipant对象 */
	 DomainParticipant* create_participant(_DOMAINID_T DomainId,
		const DomainParticipantQos& QoS, 
		DomainParticipantListener* pDomainParticipantListener,
		StatusMask mask);

	/* Nephalem 删除域参与者 */
	 ReturnCode_t delete_participant(DomainParticipant* & pDomainParticipant);

	/* Nephalem 规范中定义为随机返回一个DomainParticipant，此处存在线程安全问题 */
	 DomainParticipant* lookup_participant(_DOMAINID_T DomainId);

	/* Nephalem 设置默认的DomainParticipantQoS，不兼容则设置失败 */
	 ReturnCode_t set_default_participant_qos(const DomainParticipantQos& QoS);

	/* Nephalem 获取DomainParticipantQoS默认值 */
	 ReturnCode_t get_default_participant_qos(DomainParticipantQos& QoS);

	/* Nephalem 设置默认的DomainParticipantFactoryQos，不兼容则设置失败 */
	 ReturnCode_t set_qos(const DomainParticipantFactoryQos& QoS);

	/* Nephalem 获取DomainParticipantFactoryQos默认值 */
	 ReturnCode_t get_qos(DomainParticipantFactoryQos& QoS);

	/* Nephalem 单例模式 */
	static DomainParticipantFactory* get_instance();
	
private:

	/* Nephalem 不允许外部创建对象 */
	DomainParticipantFactory();

	static DomainParticipantFactory* m_pDomainParticipantFactoryInstance;

	 DomainParticipantFactoryImpl* m_pDomainParticipantFactoryImpl;
};

#endif
