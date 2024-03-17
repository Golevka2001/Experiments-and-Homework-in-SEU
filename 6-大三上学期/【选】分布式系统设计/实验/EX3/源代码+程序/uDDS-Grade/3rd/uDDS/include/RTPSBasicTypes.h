#pragma once
#include "QoSPolicy.h"
#include "uLinxDataType.h"
#include <string.h>



//*Nephalem
//��С����Ϣ
typedef Octet EncapsulationKind[2];
const EncapsulationKind CDR_BE = { 0x00,0x00 };
const EncapsulationKind CDR_LE = { 0x00,0x01 };
const EncapsulationKind PL_CDR_BE = { 0x00,0x02 };
const EncapsulationKind PL_CDR_LE = { 0x00,0x03 };




/* Nephalem ����ParticipantTopicʹ�õ��������� */
struct SPDPdiscoveredParticipantData : ParticipantBuiltinTopicData
{

	/* Nephalem ��������ʱ�� */
	Time_t						recvTime;
};

struct DiscoveredReaderData : SubscriptionBuiltinTopicData
{
	/* Nephalem �Ѿ�����ReaderProxy���ʺ�����ֱ��ʹ�� */
	//ReaderProxy					mReaderProxy;
	/* Nephalem ֱ�ӽ��淶��ReaderProxy������ֱ��չ�� */
	GUID_t						remoteReaderGuid;
	bool						expectsInlineQos;
	_LOCATOR_LIST_T				unicastLocatorList;
	_LOCATOR_LIST_T             multicastLocatorList;

	//ContentFilterProperty contentFilterProperty;
};


struct DiscoveredWriterData : PublicationBuiltinTopicData
{
	/* Nephalem �Ѿ�����WriterProxy���ʺ�����ֱ��ʹ�� */
	//WriterProxy					mWriterProxy;
	/* Nephalem ֱ�ӽ��淶��WriterProxy������ֱ��չ�� */
	GUID_t						remoteWriterGuid;
	_LOCATOR_LIST_T				unicastLocatorList;
	_LOCATOR_LIST_T             multicastLocatorList;
};
