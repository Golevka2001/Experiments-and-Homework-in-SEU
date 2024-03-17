/************************************************************
** 文件名：BasicTypes.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-10
** 修改人：无
** 日  期：无
** 描  述：BasicTypes头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _GLOBAL_BASICTYPES_H_INCLUDED_
#define _GLOBAL_BASICTYPES_H_INCLUDED_

#include "SEQ/Sequence.h"
#include "uLinxDataType.h"
//#include "ReturnCode.h"
#include <vector>
#include <list>
#include <map>
#include <utility>
#include <string>
#include <queue>
#include <set>
#include <cstring>
using std::vector;
using std::list;
using std::map;
using std::pair;
using std::string;
using std::make_pair;
using std::queue;
using std::set;

//test
#include <iostream>

using std::cout;
using std::endl;
using std::string;

#define SHOWINFO()  \
printf("%d %s Error\n", __LINE__, __func__);

typedef sequence<string> StringSeq;

#define MIG_RTPS_KEY_HASH_MAX_LENGTH 16

struct MIGRtpsKeyHash
{
	unsigned char value[MIG_RTPS_KEY_HASH_MAX_LENGTH];

	unsigned int length;

	MIGRtpsKeyHash()
	{
		memset(value, 0, MIG_RTPS_KEY_HASH_MAX_LENGTH);
		length = MIG_RTPS_KEY_HASH_MAX_LENGTH;
	}

	bool operator == (MIGRtpsKeyHash & right) const
	{
		if (this->length != right.length)
			return false;

		for (unsigned int i = 0; i < this->length; i++)
		{
			if (this->value[i] != right.value[i])
				return false;
		}

		return true;
	}

	MIGRtpsKeyHash& operator = (const MIGRtpsKeyHash & right)
	{
		this->length = right.length;

		memcpy(this->value, right.value, this->length);

		return *this;
	}
	
};

/* Nephalem 临时定义的类型 */
struct InstanceHandle_t 
{
	/*e We use guid to represent an instance */
	struct MIGRtpsKeyHash keyHash;

	int isValid;

	InstanceHandle_t():isValid(0)
	{
	}
};

const InstanceHandle_t HANDLE_NIL;
typedef sequence<InstanceHandle_t> InstanceHandleSeq;


typedef unsigned int SampleStateKind;
typedef unsigned int ViewStateKind;
typedef unsigned int InstanceStateKind;

/*
* @ brief 定义时间格式Time_t
*/
struct Time_t 
{
    int lSecond;
    unsigned int ulNanosec;
	
	//Time_t()
	//{
	//	lSecond = 0;
	//	ulNanosec = 0;
	//}

	//Time_t(const Time_t & right)
	//{
	//	lSecond = right.lSecond;
	//	ulNanosec = right.ulNanosec;
	//}

    //重载运算符 <=
    bool operator <= (const Time_t &Right) const 
    {
        if (this->lSecond > Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond < Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec > Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //重载运算符 <
    bool operator < (const Time_t &Right) const 
    {
        if (this->lSecond > Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond < Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec >= Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //重载运算符 >=
    bool operator >= (const Time_t &Right) const 
    {
        if (this->lSecond < Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond > Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec < Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //重载运算符 >
    bool operator > (const Time_t &Right) const 
    {
        if (this->lSecond < Right.lSecond) 
        {
            return false;
        }
        else if (this->lSecond > Right.lSecond) 
        {
            return true;
        }
        else if (this->ulNanosec <= Right.ulNanosec) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //重载运算符 ==
    bool operator == (const Time_t &Right) const 
    {
        if (this->lSecond == Right.lSecond &&
            this->ulNanosec == Right.ulNanosec) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 !=
    bool operator != (const Time_t &Right) const 
    {
        if (this->lSecond == Right.lSecond &&
            this->ulNanosec == Right.ulNanosec) 
        {
                return false;
        }
        else 
        {
            return true;
        }
    }

    ////重载运算符 +
    //Time_t operator + (const Time_t &Right) const 
    //{
    //    Time_t Temp = *this;
    //    if (Right.ulNanosec + Temp.ulNanosec >= (unsigned long)-1) 
    //    {
    //        ++ Temp.lSecond;
    //    }
    //    Temp.ulNanosec += Right.ulNanosec;
    //    Temp.lSecond += Right.lSecond;

    //    return Temp;
    //}

    ////重载运算符 -
    //Time_t operator - (const Time_t &Right) const 
    //{
    //    Time_t Temp = *this;
    //    if (Temp.ulNanosec - Right.ulNanosec < 0) 
    //    {
    //        -- Temp.lSecond;
    //    }
    //    Temp.ulNanosec -= Right.ulNanosec;
    //    Temp.lSecond -= Right.lSecond;

    //    return Temp;
    //}

	//修改2013-8-1
	//重载运算符 +
    Time_t operator + (const Time_t &Right) const 
    {
        Time_t Temp = *this;
        if (Right.ulNanosec + Temp.ulNanosec >= 1000000000) 
        {
            ++ Temp.lSecond;
			Temp.ulNanosec = Temp.ulNanosec+Right.ulNanosec-1000000000;
        }
		else
			Temp.ulNanosec = Temp.ulNanosec+Right.ulNanosec;
        
        Temp.lSecond += Right.lSecond;

        return Temp;
    }

    //重载运算符 -
    Time_t operator - (const Time_t &Right) const 
    {
        Time_t Temp = *this;
        //if (Temp.ulNanosec - Right.ulNanosec < 0) 
		if (Temp.ulNanosec < Right.ulNanosec) 
        {
            -- Temp.lSecond;
			Temp.ulNanosec = Temp.ulNanosec+1000000000-Right.ulNanosec;
        }
		else
			Temp.ulNanosec -= Right.ulNanosec;

        Temp.lSecond -= Right.lSecond;

        return Temp;
	}

		//大数据，重载运算符/
	Time_t operator / (const unsigned long &Right) const 
    {
        Time_t Temp = *this;
		Time_t Result;
		//double dTempb = Temp.lSecond + Temp.ulNanosec / 1000000000.0;
        //double dTempa = dTempb/Right;
        //Temp.lSecond = floor(dTempa);
		//Temp.ulNanosec = (dTempa - floor(dTempa))*1000000000;
		Result.lSecond = (Temp.lSecond*1000000000+Temp.ulNanosec)/(Right*1000000000);
		Result.ulNanosec = ((Temp.lSecond*1000000000+Temp.ulNanosec)-((Temp.lSecond*1000000000+Temp.ulNanosec)/(Right*1000000000))*(Right*1000000000))/Right;
        return Result;
    }
};

//时间信息
typedef Time_t Duration_t;

//时间0
const Time_t TIME_ZERO      = { 0, 0 };
//非法时间
const Time_t TIME_INVALID   = { -1, 0xffffffff };
//最大时间
const Time_t TIME_INFINITE  = { 0x7fffffff, 0xffffffff };
//lifespan 默认1min
const Time_t TIME_ONE_MINUTE   = { 60, 0 };

const Time_t TIME_TWO_SECONDS = {2,0};

//回复心跳信息的延时
const Duration_t HEARTBEAT_RESPONSE_DELAY       = { 0, /*测试Nephalem500000000*/100000000 };
//心跳信息忽略时间
const Duration_t HEARTBEAT_SUPPRESSION_DURATION = { 0, 0 };
//心跳信息重发时间
const Duration_t HEARTBEAT_PERIOD               = { 0,  /*测试Nephalem400000000*/100000000 };
//nack信息回复延时
const Duration_t NACK_RESPONSE_DELAY            = { 0,  /*测试Nephalem200000000*/50000000 };
//nack信息忽略时间
const Duration_t NACK_SUPPRESSION_DURATION      = { 0, 0 };


/**
* @ brief 定义数据的序列号 64bit
* @       重载部分运算符
*/
struct SequenceNumber_t 
{
    int lHigh;
    unsigned int ulLow;

    //默认构造函数 赋值为-1 表示错误的序列号
    SequenceNumber_t () 
    {
        this->lHigh = -2;
        this->ulLow = 0;
    }

    //构造函数
    SequenceNumber_t (const long lSeqhigh, const unsigned long ulSeqlow) 
    {
        this->lHigh = lSeqhigh;
        this->ulLow = ulSeqlow;
    }

    //赋值方法 ()
    SequenceNumber_t operator () (const long lSeqhigh, const unsigned long ulSeqlow) 
    {
        this->lHigh = lSeqhigh;
        this->ulLow = ulSeqlow;

        return *this;
    }

    //重载运算符 <
    bool operator < (const SequenceNumber_t &Right) const 
    {
        if (this->lHigh < Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh > Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow < Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 <=
    bool operator <= (const SequenceNumber_t &Right) const 
    {
        if (this->lHigh < Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh > Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow <= Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 >
    bool operator > (const SequenceNumber_t &Right) const 
    {
        if (this->lHigh > Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh < Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow > Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 >
    bool operator > (const long &Right) const 
    {
        if (this->lHigh > 0) 
        {
            return true;
        }
        else if (this->lHigh < 0) 
        {
            return false;
        }
        else if (this->ulLow > (unsigned long)Right) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 >=
    bool operator >= (const SequenceNumber_t &Right) const 
    {
        if (this->lHigh > Right.lHigh) 
        {
            return true;
        }
        else if (this->lHigh < Right.lHigh) 
        {
            return false;
        }
        else if (this->ulLow >= Right.ulLow) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 !=
    bool operator != (const SequenceNumber_t &Right) const 
    {
        if ((this->lHigh == Right.lHigh) && (this->ulLow == Right.ulLow)) 
        {
            return false;
        }
        else 
        {
            return true;
        }
    }

    //重载运算符 ==
    bool operator == (const SequenceNumber_t &Right) const 
    {
        if ((this->lHigh == Right.lHigh) && (this->ulLow == Right.ulLow)) 
        {
            return true;
        }
        else 
        {
            return false;
        }
    }

    //重载运算符 =
    SequenceNumber_t operator = (const SequenceNumber_t &Right) 
    {
        this->lHigh = Right.lHigh;
        this->ulLow = Right.ulLow;

        return *this;
    }

    //重载运算符 =
    SequenceNumber_t operator = (const unsigned long &Right) 
    {
        this->lHigh = 0;
        this->ulLow = Right;

        return *this;
    }

    //重载运算符 前置++
    SequenceNumber_t operator ++ () 
    {
        ++ (this->ulLow);
        if (this->ulLow == 0)
        {
            ++ (this->lHigh);
        }

        return *this;
    }

    //重载运算符 后置++
    SequenceNumber_t operator ++ (int) 
    {
        SequenceNumber_t Temp;
        Temp.lHigh = this->lHigh;
        Temp.ulLow = this->ulLow;
        this->ulLow ++;
        if (this->ulLow == 0)
        {
            this->lHigh ++;
        }

        return Temp;
    }

    //重载运算符 前置--
    SequenceNumber_t operator -- () 
    {
        if (this->ulLow == 0) 
        {
            -- (this->lHigh);
        }
        -- (this->ulLow);

        return *this;
    }

    //重载运算符 后置--
    SequenceNumber_t operator -- (int)
    {
        SequenceNumber_t Temp;
        Temp.lHigh = this->lHigh;
        Temp.ulLow = this->ulLow;
        if (this->ulLow == 0) 
        {
            -- (this->lHigh);
        }
        -- (this->ulLow);

        return Temp;
    }

    //重载运算符 +
    SequenceNumber_t operator + (const long Add) const 
    {
        SequenceNumber_t Temp = *this;
        ////cout<<Temp.ulLow<<" "<<Add<<" "<<(unsigned long)-1<<endl;
        if (Temp.ulLow  > (unsigned long)-1 - Add)
        {
            ++ Temp.lHigh;
        }
        Temp.ulLow += Add;

        return Temp;
    }

    //重载运算符 +
    SequenceNumber_t operator + (const SequenceNumber_t &Right) const 
    {
        SequenceNumber_t Temp = *this;
        if (Temp.ulLow  > (unsigned long)-1 - Right.ulLow)
        {
            ++ Temp.lHigh;
        }
        Temp.ulLow += Right.ulLow;
        Temp.lHigh += Right.lHigh;

        return Temp;
    }

    //重载运算符 -
    SequenceNumber_t operator - (const long Sub) const 
    {
        SequenceNumber_t Temp = *this;
        if (Temp.ulLow < (unsigned long)Sub)
        {
            -- Temp.lHigh;
        }
        Temp.ulLow -= Sub;

        return Temp;
    }

    //重载运算符 -
    SequenceNumber_t operator - (const SequenceNumber_t &Right) const 
    {
        SequenceNumber_t Temp = *this;
        if (Temp.ulLow < Right.ulLow)
        {
            -- Temp.lHigh;
        }
        Temp.ulLow -= Right.ulLow;
        Temp.lHigh -= Right.lHigh;

        return Temp;
    }

    //重载运算符 +=
    SequenceNumber_t operator += (const long lAdd) 
    {
        if (this->ulLow  > (unsigned long)-1 - lAdd)
        {
            ++ this->lHigh;
        }
        this->ulLow += lAdd;

        return *this;
    }

    //重载运算符 -=
    SequenceNumber_t operator -= (const long lSub)
    {
        if (this->ulLow - lSub < 0)
        {
            -- this->lHigh;
        }
        this->ulLow -= lSub;

        return *this;
    }
};

//未知序列号
const SequenceNumber_t SEQUENCENUMBER_UNKNOWN;

/* Nephalem 0值 */
const SequenceNumber_t SEQUENCENUMBER_ZERO(0,0);

//序列号队列
typedef queue<SequenceNumber_t> _SEQ_NUM_QUEUE;

/**
* @ brief 定义数据域
*/
typedef int _DOMAINID_T;

/**
* @ brief 定义序号
*/
typedef int _COUNT_T;

/**
* @ brief 定义Change的类型
*/
typedef unsigned short _CHANGE_KIND_T;
#define ALIVE                   0x0001 << 0
#define NOT_ALIVE_DISPOSED      0x0001 << 1
#define NOT_ALIVE_UNREGISTERED  0x0001 << 2
#define ALIVE_UD				0x0011
#define ALIVE_FRAG				0x0111

enum _ENTITY_STATUS_T
{
	CREATION,
	DELETION
};

typedef long _RELIABILITY_KIND_T;
#define BEST_EFFORT 1
#define RELIABLE 2

/* Nephalem RTPS 规范中定义的GUID*/
typedef Octet guidPrefix_t[12];
const guidPrefix_t GUIDPREFIX_UNKNOWN = { \
	0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00, 0x00 };

/**
* @ brief 定义entityId
*/
typedef octet OctetArray3[3];
struct EntityId_t
{
	OctetArray3 entityKey;
	octet entityKind;

	//重载运算符 =
	EntityId_t operator = (const EntityId_t &Right)
	{
		memcpy(&this->entityKey, &Right.entityKey, sizeof(OctetArray3));
		memcpy(&this->entityKind, &Right.entityKind, sizeof(octet));

		return *this;
	}
	//重载运算符 <
	bool operator < (const EntityId_t &Right) const
	{
		for (int I = 0; I < 3; ++I)
		{
			if (this->entityKey[I] < Right.entityKey[I])
			{
				return true;
			}
			else if (this->entityKey[I] > Right.entityKey[I])
			{
				return false;
			}
		}
		if (this->entityKind < Right.entityKind)
		{
			return true;
		}
		return false;
	}
	//重载运算符 >
	bool operator > (const EntityId_t &Right) const
	{
		for (int I = 0; I < 3; ++I)
		{
			if (this->entityKey[I] > Right.entityKey[I])
			{
				return true;
			}
			else if (this->entityKey[I] < Right.entityKey[I])
			{
				return false;
			}
		}
		if (this->entityKind > Right.entityKind)
		{
			return true;
		}
		return false;
	}
	//重载运算符 >=
	bool operator >= (const EntityId_t &Right) const
	{
		for (int I = 0; I < 3; ++I)
		{
			if (this->entityKey[I] > Right.entityKey[I])
			{
				return true;
			}
			else if (this->entityKey[I] < Right.entityKey[I])
			{
				return false;
			}
		}
		if (this->entityKind >= Right.entityKind)
		{
			return true;
		}
		return false;
	}
	//重载运算符 <=
	bool operator <= (const EntityId_t &Right) const
	{
		for (int I = 0; I < 3; ++I)
		{
			if (this->entityKey[I] < Right.entityKey[I])
			{
				return true;
			}
			else if (this->entityKey[I] > Right.entityKey[I])
			{
				return false;
			}
		}
		if (this->entityKind <= Right.entityKind)
		{
			return true;
		}
		return false;
	}
	//重载运算符 ==
	bool operator == (const EntityId_t &Right)
	{
		int N = 0;
		while (N < 3)
		{
			if (this->entityKey[N] != Right.entityKey[N])
				return false;
			++N;
		}
		if (this->entityKind != Right.entityKind)
			return false;

		return true;
	}

	bool operator == (const EntityId_t &Right)const 
	{
		int N = 0;
		while (N < 3)
		{
			if (this->entityKey[N] != Right.entityKey[N])
				return false;
			++N;
		}
		if (this->entityKind != Right.entityKind)
			return false;

		return true;
	}
	//重载运算符 !=
	bool operator != (const EntityId_t &Right)
	{
		int N = 0;
		while (N < 3)
		{
			if (this->entityKey[N] != Right.entityKey[N])
				return true;
			++N;
		}
		if (this->entityKind != Right.entityKind)
			return true;

		return false;
	}

	void show()
	{
		for (int i = 0; i < 3; i++)
			printf("%u.", entityKey[i]);
		printf("%u.", entityKind);
	}
};

/* Nephalem RTPS规范中定义的RTPS版本结构 */
struct ProtocolVersion_t
{
	octet major;
	octet minor;
};

const ProtocolVersion_t PROTOCOLVERSION_1_0 = { 1,0 };
const ProtocolVersion_t PROTOCOLVERSION_1_1 = { 1,1 };
const ProtocolVersion_t PROTOCOLVERSION_2_0 = { 2,0 };
const ProtocolVersion_t PROTOCOLVERSION_2_1 = { 2,1 };
const ProtocolVersion_t PROTOCOLVERSION_2_2 = { 2,2 };
#define PROTOCOLVERSION PROTOCOLVERSION_2_2

#define DOMAINID_TYPE_NATIVE 			int
#define HANDLE_TYPE_NATIVE				int
#define HANDLE_NIL_NATIVE 				0
#define BUILTIN_TOPIC_KEY_TYPE_NATIVE 	int

/*
*Nephalem ParameterID定义
*/
#define PID_PAD								   0x0000
#define PID_SENTINEL						   0x0001
#define PID_PARTICIPANT_LEASE_DURATION		   0x0002
#define PID_PERSISTENCE						   0x0003
#define PID_TIME_BASED_FILTER			  	   0x0004
#define PID_TOPIC_NAME						   0x0005
#define PID_OWNERSHIP_STRENGTH                 0x0006
#define PID_TYPE_NAME                          0x0007
#define PID_METATRAFFIC_MULTICAST_IPADDRESS    0x000d
#define PID_DEFAULT_UNICAST_IPADDRESS	       0x000c
#define PID_DEFAULT_UNICAST_PORT		       0x000e
#define PID_EXPECTS_ACK					       0x0010
#define PID_MULTICAST_IPADDRESS			       0x0011
#define PID_SEND_QUEUE_SIZE                    0x0013
#define PID_PROTOCOL_VERSION		           0x0015
#define PID_VENDOR_ID				           0x0016
#define PID_RECV_QUEUE_SIZE				       0x0018
#define PID_RELIABLITY                         0x001a
#define PID_LIVENESS					       0x001b
#define PID_DURABILITY				    	   0x001d
#define PID_DURABILITY_SERVICE			       0x001e
#define PID_OWNERSHIP					       0x001f
#define PID_PRESENTATION				       0x0021
#define PID_DEADLINE					       0x0023
#define PID_DESTINATION_ORDER                  0x0025
#define PID_LATENCY_BUDGET			    	   0x0027
#define PID_PARTITION				    	   0x0029
#define PID_LIFESPAN			    		   0x002b
#define PID_USER_DATA						   0x002c
#define PID_GROUP_DATA						   0x002d
#define PID_TOPIC_DATA						   0x002e
#define PID_UNICAST_LOCATOR					   0x002f
#define PID_MULTICAST_LOCATOR				   0x0030
#define PID_DEFAULT_UNICAST_LOCATOR			   0x0031
#define PID_METATRAFFIC_UNICAST_LOCATOR		   0x0032
#define PID_METATRAFFIC_MULTICAST_LOCATOR	   0x0033
#define PID_PARTICIPANT_MANUAL_LIVELINESS_COUNT 0x0034
#define PID_CONTENT_FILTER_PROPERTY		       0x0035
#define PID_HISTORY							   0x0040
#define PID_RESOURCE_LIMITS					   0x0041
#define PID_EXPECTS_INLINE_QOS				   0x0043
#define PID_PARTICIPANT_BUILTIN_ENDPOINTS	   0x0044
#define PID_METATRAFFIC_MULTICAST_PORT	       0x0046
#define PID_DEFAULT_MULTICAST_LOCATOR		   0x0048
#define PID_TRANSPORT_PRIORITY			       0x0049
#define PID_PARTICIPANT_GUID			       0x0050
#define PID_PARTICIPANT_ENTITYID			   0x0051
#define PID_GROUP_GUID						   0x0052
#define PID_GROUP_ENTITY_ID					   0x0053
#define PID_ENDPOINT_GUID					   0x005a
#define PID_BUTLTIN_ENDPOINT_SET		       0x0058
#define PID_PROPERTY_LIST					   0x0059
#define PID_TYPE_MAX_SIZE_SERIALIZED		   0x0060
#define PID_ENTITY_NAME						   0x0062
#define PID_KEY_HASH						   0x0070
#define PID_STATUS_INFO					       0x0071
#define PID_TYPE_OBJECT						   0x0072
#define PID_TYPE_CONSISTENCY				   0x0074
#define PID_PRODUCT_VERSION				       0x8000
#define PID_ENTITY_VIRTUAL_GUID				   0x8002
#define PID_SERVICE_KIND					   0x8003
#define PID_TYPE_CODE						   0x8004
#define PID_DISABLE_POSITIVE_ACKS			   0x8005
#define PID_EXPECTS_VIRTUAL_HB				   0x8009
#define PID_ACK_KIND				           0x800b
#define PID_PEER_HOST_EPOCH					   0X800e
#define PID_DOMAIN_ID					       0X800F
#define PID_TRANSPORT_INFO_LIST				   0X8010
#define PID_DIRECT_COMMUNICATION			   0x8011
#define PID_STATUS					           0x1115

#define PEER_HOST_EPOCH						   0x00



//OMG规范定义的entityKind
//未知实体
#define ENTITYKIND_USER_UNKNOWN             0x00
//内置未知端点
#define ENTITYKIND_BUILTIN_UNKNOWN          0xc0
//内置域参与者端点
#define ENTITYKIND_BUILTIN_PARTICIPANT      0xc1
//用户带key发布端
#define ENTITYKIND_USER_WRITER_WITH_KEY     0x02
//内置带key发布端
#define ENTITYKIND_BUILTIN_WRITER_WITH_KEY  0xc2
//用户发布端
#define ENTITYKIND_USER_WRITER_NO_KEY       0x03
//内置发布端
#define ENTITYKIND_BUILTIN_WRITER_NO_KEY    0xc3
//用户带key订阅端
#define ENTITYKIND_USER_READER_WITH_KEY     0x07
//内置带key订阅端
#define ENTITYKIND_BUILTIN_READER_WITH_KEY  0xc7
//用户订阅端
#define ENTITYKIND_USER_READER_NO_KEY       0x04
//内置订阅端
#define ENTITYKIND_BUILTIN_READER_NO_KEY    0xc4

//定义内置对象的entityId
//未知实体entityId
const EntityId_t ENTITYID_UNKNOW = { 0x00, 0x00, 0x00, 0x00 };
//域参与者entityId
const EntityId_t ENTITYID_PARTICIPANT = { 0x00, 0x00, 0x01, 0xc1 };
//内置主题发布端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_TOPIC_WRITER = { 0x00, 0x00, 0x02, 0xc2 };
//内置主题订阅端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_TOPIC_READER = { 0x00, 0x00, 0x02, 0xc7 };
//内置发布信息发布端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_WRITER = { 0x00, 0x00, 0x03, 0xc2 };
//内置发布定西订阅端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_PUBLICATIONS_READER = { 0x00, 0x00, 0x03, 0xc7 };
//内置订阅信息发布端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_WRITER = { 0x00, 0x00, 0x04, 0xc2 };
//内置订阅信息订阅端entityId
const EntityId_t ENTITYID_SEDP_BUILTIN_SUBSCRIPTIONS_READER = { 0x00, 0x00, 0x04, 0xc7 };
//内置域参与者发布端entityId
const EntityId_t ENTITYID_SPDP_BUILTIN_PARTICIPANT_WRITER = { 0x00, 0x01, 0x00, 0xc2 };
//内置域参与者订阅端entityId
const EntityId_t ENTITYID_SPDP_BUILTIN_PARTICIPANT_READER = { 0x00, 0x01, 0x00, 0xc7 };
//内置域参与者信息发布端entityId
const EntityId_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_WRITER = { 0x00, 0x02, 0x00, 0xc2 };
//内置域参与者信息订阅端entityId
const EntityId_t ENTITYID_P2P_BUILTIN_PARTICIPANT_MESSAGE_READER = { 0x00, 0x02, 0x00, 0xc7 };

/* Nephalem RTPS规范中定义的结构*/
/* Nephalem 规范中要求 guidPrefix[0] = vendorId[0]，guidPrefix[1] = vendorId[1] */
struct GUID_t
{
	guidPrefix_t guidPrefix;
	EntityId_t entityId;

	GUID_t()
	{
		memset(this->guidPrefix, 0, sizeof(guidPrefix_t));
		this->entityId = ENTITYID_UNKNOW;
	}
	GUID_t(guidPrefix_t Prefix, EntityId_t Id)
	{
		memcpy(this->guidPrefix, Prefix, sizeof(guidPrefix_t));
		this->entityId = Id;
	}

	//重载运算符==
	bool operator ==(const GUID_t &Right)
	{
		int M = 0;
		while (M < 12)
		{
			if (this->guidPrefix[M] != Right.guidPrefix[M])
				return false;
			++M;
		}
		if (this->entityId != Right.entityId)
			return false;

		return true;
	}

	//重载运算符 !=
	bool operator != (const GUID_t &Right)
	{
		int M = 0;
		while (M < 12)
		{
			if (this->guidPrefix[M] != Right.guidPrefix[M])
				return true;
			++M;
		}
		if (this->entityId != Right.entityId)
			return true;

		return false;
	}

	//重载运算符 <
	bool operator < (const GUID_t &Right) const
	{
		int M = 0;
		while (M < 12)
		{
			if (this->guidPrefix[M] > Right.guidPrefix[M])
			{
				return false;
			}
			else if (this->guidPrefix[M] < Right.guidPrefix[M])
			{
				return true;
			}
			++M;
		}
		if (this->entityId < Right.entityId)
			return true;

		return false;
	}

	//重载运算符 >
	bool operator > (const GUID_t &Right) const
	{
		int M = 0;
		while (M < 12)
		{
			if (this->guidPrefix[M] < Right.guidPrefix[M])
			{
				return false;
			}
			else if (this->guidPrefix[M] > Right.guidPrefix[M])
			{
				return true;
			}
			++M;
		}
		if (this->entityId > Right.entityId)
			return true;

		return false;
	}

	//重载运算符 =
	GUID_t operator = (const GUID_t &Right)
	{
		memcpy(this->guidPrefix, Right.guidPrefix, sizeof(guidPrefix_t));
		this->entityId = Right.entityId;

		return *this;
	}
	GUID_t operator = (const guidPrefix_t &Right)
	{
		memcpy(this->guidPrefix, guidPrefix, sizeof(guidPrefix_t));
		return *this;
	}

	void show()
	{
		for (int i = 0; i < 12; i++)
			printf("%u.", guidPrefix[i]);
		entityId.show();
	}
};

const GUID_t GUID_UNKNOWN;





/* Nephalem RTPS规范中定义的厂商编号 */
typedef octet OctetArray2[2];
struct VendorId_t
{
	OctetArray2 vendorId;
};
const VendorId_t VENDORID_UNKNOWN = { 0,0 };

const VendorId_t VENDORID_SEU = { 0x08, 0x08 };


/* Nephalem RTPS规范中定义的类型，表明支持的SEDP端点的类型 */
typedef unsigned int BuiltinEndpointSet_t;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER  0x00000001 << 0
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR   0x00000001 << 1
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER  0x00000001 << 2
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR   0x00000001 << 3
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER 0x00000001 << 4
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR  0x00000001 << 5


/* Nephalem RTPS规范中定义的定位器 */
/* KIND为LOCATOR_KIND_UDPv4时，address前8个字节为0 */
typedef octet OctetArray16[16];

const int LOCATOR_KIND_UDPV4 = 0x00000001;
const int LOCATOR_KIND_UDPV6 = 0x00000002;
const int LOCATOR_KIND_SHMEM = 0x01000000;
struct Locator_t
{
	int kind;
	unsigned int port;
	OctetArray16 address;

	/* Nephalem 需要初始化，否则在对外互操作时可能异常 */
	Locator_t() :kind(0), port(0)
	{
		memset(address, 0, 16);
	}

	bool operator < (const Locator_t& locator) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (this->address[i] < locator.address[i])
				return true;

			if (this->address[i] > locator.address[i])
				return false;
		}

		if (this->port < locator.port)
			return true;

		if (this->kind < locator.kind)
			return true;

		return false;
	}


	bool operator > (const Locator_t& locator) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (this->address[i] > locator.address[i])
				return true;

			if (this->address[i] < locator.address[i])
				return false;
		}

		if (this->port > locator.port)
			return true;

		if (this->kind > locator.kind)
			return true;

		return false;
	}

	bool operator == (Locator_t& locator) const
	{
		for (int i = 0; i < 16; i++)
		{
			if (this->address[i] != locator.address[i])
				return false;
		}

		if (this->port != locator.port)
			return false;

		if (this->kind != locator.kind)
			return false;

		return true;
	}
};
typedef list< Locator_t> _LOCATOR_LIST_T;

//const _LOCATOR_T LOCATOR_INVALID;
//定义默认端口Port
#define PORT_BASE_NUMBER 7400
#define DOMAINID_GAIN 250
#define PARTICIPANTID_GAIN	2
#define ADDITIONAL_OFFSETS_D0 0
#define ADDITIONAL_OFFSETS_D1 10
#define ADDITIONAL_OFFSETS_D2 1
#define ADDITIONAL_OFFSETS_D3 11
//多播发现端口
#define SPDP_WELL_KNOWN_MULTICAST_PORT(ulDomainId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D0
//单播发现端口
#define SPDP_WELL_KNOWN_UNICAST_PORT(ulDomainId, ulParticipantId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D1 + \
    PARTICIPANTID_GAIN * (unsigned long)ulParticipantId
//用户多播端口
#define USER_DEFAULT_MULTICAST_PORT(ulDomainId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D2
//用户单播端口
#define USER_DEFAULT_UNICAST_PORT(ulDomainId, ulParticipantId) \
    PORT_BASE_NUMBER + DOMAINID_GAIN * (unsigned long)ulDomainId + ADDITIONAL_OFFSETS_D3 + \
    PARTICIPANTID_GAIN * (unsigned long)ulParticipantId


#define LOCATOR_INVALID {LOCATOR_KIND_INVALID, LOCATOR_PORT_INVALID,LOCATOR_ADDRESS_INVALID}
#define LOCATOR_KIND_INVALID	-1
#define LOCATOR_ADDRESS_INVALID {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define LOCATOR_PORT_INVALID	0
#define LOCATOR_KIND_RESERVED	0
#define LOCATOR_KIND_UDPv4		1
#define LOCATOR_KIND_UDPv6		2



struct Count_t
{
	int value;
};


struct Property_t
{
	string name;
	string value;
};

typedef short ParameterId_t;

struct ParameterHeader
{
	ParameterId_t parameterId;
	short length;
};

struct Parameter : ParameterHeader
{
	octet value[128]; // Pseudo-IDL: array of non-const length
};

typedef list<Parameter> _PARAMETER_LIST;

struct _CACHE_CHANGE
{
	_CHANGE_KIND_T Kind;
	GUID_t WriterGuid;
	InstanceHandle_t InstanceHandle;
	SequenceNumber_t SequenceNumber;
	Time_t Timestamp;
	unsigned int uiLength;
	char *pDatavalue;
	_PARAMETER_LIST InlineQos;

	/* Nephalem 分片数据的接收状态 */
	//_FRAGMENT_NUMBER_SET FragmentNumberState;

	/* Nephalem 接收的最大的分片数据编号 */
	unsigned int uiFragNum;

	/* Nephalem 分片总数 */
	unsigned int uiFragTotal;

	set<unsigned short> lossFragNumber;

	_CACHE_CHANGE() :uiLength(0), pDatavalue(NULL), uiFragNum(0),uiFragTotal(0)
	{
	}

	~_CACHE_CHANGE()
	{
		if (NULL != pDatavalue)
			delete pDatavalue;
	}
};

/**
* @ brief 定义CacheChange的列表格式
*/
typedef list<_CACHE_CHANGE*> _CACHE_CHANGE_LIST_T;

enum ChangeFromWriterStatusKind
{
	LOST,
	MISSING,
	RECEIVRD,
	UNKNOWN
};

enum ChangeForReaderStatusKind
{
	UNSENT,
	UNACKNOWLEDGED,
	REQUESTED,
	ACKNOWLEDGED,
	UNDERWAY
};

/* Nephalem 将ChangeFromWriter与CacheChange关联 */
struct ChangeFromWriter
{
	ChangeFromWriterStatusKind	status;
	bool						is_relevant;
	_CACHE_CHANGE*				pRelatedCacheChange;

	ChangeFromWriter() :status(UNKNOWN), is_relevant(false), pRelatedCacheChange(NULL) {}

	~ChangeFromWriter()
	{
		pRelatedCacheChange = NULL;
	}
};
typedef map<SequenceNumber_t, ChangeFromWriter> ChangeFromWriterMap;

struct ChangeForReader
{
	ChangeForReaderStatusKind	status;
	bool						is_relevant;
	SequenceNumber_t			SequenceNumber;
	//const _CACHE_CHANGE*				pRelatedCacheChange;

	ChangeForReader() :status(UNSENT), is_relevant(false)/*, pRelatedCacheChange(NULL) */{}
};
typedef map<SequenceNumber_t, ChangeForReader> ChangeForReaderMap;

/**
* @ brief 定义WriterProxy的列表格式
*/
class WriterProxy;
typedef map<GUID_t, WriterProxy*> _WRITER_PROXY_LIST_T;

/**
* @ brief 定义ReaderProxy队列
*/
class ReaderProxy;
typedef map<GUID_t, ReaderProxy*> _READER_PROXY_LIST;

//struct DiscoveredTopicData
//{
//	DDS::TopicBuiltinTopicData ddsTopicData;
//};

/* Nephalem  DDS规范中定义 内置主题的关键字 */
struct BuiltinTopicKey_t
{
	BUILTIN_TOPIC_KEY_TYPE_NATIVE value[3];
};

/**
* @ brief 定义DomainParticipa的列表格式
*/
class DomainParticipant;
class DomainParticipantImpl;
typedef list<DomainParticipant*> _DOMAIN_PARTICIPANT_LIST;
typedef list<DomainParticipantImpl*> _DOMAIN_PARTICIPANT_IMPL_LIST;
typedef map<_DOMAINID_T, _DOMAIN_PARTICIPANT_LIST> _DOMAIN_PARTICIPANT_MAP;
typedef map<_DOMAINID_T, _DOMAIN_PARTICIPANT_IMPL_LIST> _DOMAIN_PARTICIPANT_IMPL_MAP;

#include <set>
using std::set;
typedef string _TYPE;
class Publisher;
class PublisherImpl;
class Subscriber;
class SubscriberImpl;
class Topic;
class TopicDescription;
class DataWriter;
class DataWriterImpl;
class DataReader;
class DataReaderImpl;
class ContentFilteredTopic;
class Filter;
class TopicImpl;
typedef list <Publisher*> _PUBLISHER_LIST_T;
typedef list <PublisherImpl*> _PUBLISHER_IMPL_LIST_T;
typedef list <Subscriber*> _SUBSCRIBER_LIST_T;
typedef list <SubscriberImpl*> _SUBSCRIBER_IMPL_LIST_T;
typedef list <TopicDescription*> _TOPIC_DESCRIPTION_LIST_T;
typedef list <Topic*> _TOPIC_LIST_T;
typedef list <TopicImpl*> _TOPIC_IMPL_LIST_T;
typedef list <ContentFilteredTopic*> _CONTENT_FILTERED_TOPIC_LIST_T;
typedef list <_TYPE> _TYPE_LIST_T;
typedef set <string> _TYPE_SET_T;
typedef list <unsigned long> _IP_LIST_T;
typedef list <DataWriter*> _DATA_WRITER_LIST_T;
typedef list <DataWriterImpl*> _DATA_WRITER_IMPL_LIST_T;
typedef list <DataReader*> _DATA_READER_LIST_T;
typedef list <DataReaderImpl*> _DATA_READER_IMPL_LIST_T;


/**
* @ brief 定义主题的类型，是否有Key
*/
typedef enum 
{
    NO_KEY,
    WITH_KEY
}_TOPIC_KIND_T;

struct UserData
{
	char* pData;
	int ilength;

	UserData()
	{
		ilength = 0;
		pData = NULL;
	}

	//~UserData()
	//{
	//	if (NULL != pData)
	//		delete pData;
	//}
};

typedef vector<UserData> UserDataVector;
/**
* @ brief 定义Listener监听的状态集
*/
typedef unsigned long StatusMask;
#define STATUS_MASK_NONE                                0x00000000
#define STATUS_MASK_ALL                                 0xFFFFFFFF
#define STATUS_MASK_ON_DATA_AVAILABLE                   0x00000001 << 1
#define STATUS_MASK_ON_OFFERED_DEADLINE_MISSED          0x00000001 << 2
#define STATUS_MASK_ON_REQUESTED_DEADLINE_MISSED        0x00000001 << 3


#endif
