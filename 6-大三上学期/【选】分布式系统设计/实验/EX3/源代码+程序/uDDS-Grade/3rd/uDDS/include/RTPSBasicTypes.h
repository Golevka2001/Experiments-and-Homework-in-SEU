#pragma once
#include "QoSPolicy.h"
#include "uLinxDataType.h"
#include <string.h>



//*Nephalem
//大小端信息
typedef Octet EncapsulationKind[2];
const EncapsulationKind CDR_BE = { 0x00,0x00 };
const EncapsulationKind CDR_LE = { 0x00,0x01 };
const EncapsulationKind PL_CDR_BE = { 0x00,0x02 };
const EncapsulationKind PL_CDR_LE = { 0x00,0x03 };




/* Nephalem 内置ParticipantTopic使用的数据类型 */
struct SPDPdiscoveredParticipantData : ParticipantBuiltinTopicData
{

	/* Nephalem 新增接收时间 */
	Time_t						recvTime;
};

struct DiscoveredReaderData : SubscriptionBuiltinTopicData
{
	/* Nephalem 已经定义ReaderProxy不适合在这直接使用 */
	//ReaderProxy					mReaderProxy;
	/* Nephalem 直接将规范中ReaderProxy的内容直接展开 */
	GUID_t						remoteReaderGuid;
	bool						expectsInlineQos;
	_LOCATOR_LIST_T				unicastLocatorList;
	_LOCATOR_LIST_T             multicastLocatorList;

	//ContentFilterProperty contentFilterProperty;
};


struct DiscoveredWriterData : PublicationBuiltinTopicData
{
	/* Nephalem 已经定义WriterProxy不适合在这直接使用 */
	//WriterProxy					mWriterProxy;
	/* Nephalem 直接将规范中WriterProxy的内容直接展开 */
	GUID_t						remoteWriterGuid;
	_LOCATOR_LIST_T				unicastLocatorList;
	_LOCATOR_LIST_T             multicastLocatorList;
};
