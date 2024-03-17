/************************************************************
** 文件名：DataReaderListener.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-20
** 修改人：无
** 日  期：无
** 描  述：DataReaderListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAREADERLISTENER_H_INCLUDED_
#define _DDS_DATAREADERLISTENER_H_INCLUDED_
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "DDS/Listener/DDSListener.h"

class DataReader;
class DataWriter;

struct RequestedDeadlineMissedStatus
{

	/*e \dref_RequestedDeadlineMissedStatus_total_count
	 */
	int total_count;

	/*e \dref_RequestedDeadlineMissedStatus_total_count_change
	 */
	int total_count_change;

	/*e \dref_RequestedDeadlineMissedStatus_last_instance_handle
	 */
	//DDS_InstanceHandle_t last_instance_handle;
	RequestedDeadlineMissedStatus() : total_count(0), total_count_change(0)
	{

	}
};

enum SampleRejectedStatusKind
{
	NOT_REJECTED,
	REJECTED_BY_INSTANCES_LIMIT,
	REJECTED_BY_SAMPLES_LIMIT,
	REJECTED_BY_SAMPLES_PER_INSTANCE_LIMIT
};

struct SampleRejectedStatus
{
	long						total_count;
	long						total_count_change;
	SampleRejectedStatusKind	last_reason;
	//InstanceHandle_t			last_instance_handle;
};

struct LivelinessChangedStatus
{
	long				alive_count;
	long				not_alive_count;
	long				alive_count_change;
	long				not_alive_count_change;
	//InstanceHandle_t	last_publication_handle;
};


struct RequestedIncompatibleQosStatus
{
	long					total_count;
	long					total_count_change;
	QosPolicyId_t			last_policy_id;
	//QosPolicyCountSeq	policies;
};

struct SubscriptionMatchedStatus
{
	long				total_count;
	long				total_count_change;
	long				current_count;
	long				current_count_change;
	InstanceHandle_t	last_publication_handle;
};

struct SampleLostStatus
{
	long		total_count;
	long		total_count_change;
};

class DDS_DLL DataReaderListener : public DDSListener

{
public:
    DataReaderListener() {}

    virtual ~DataReaderListener() {}
    //成功则RETCODE_OK

    virtual void on_data_available(DataReader* the_reader)
    {	
    }

	virtual void on_sample_rejected(DataReader* the_reader, const SampleRejectedStatus& status)
	{

	}

	virtual void on_liveliness_changed(DataReader* the_reader, const LivelinessChangedStatus& status)
	{

	}

	virtual void on_requested_deadline_missed(DataReader* the_reader,const RequestedDeadlineMissedStatus& status)
	{

	}

	virtual void on_requested_incompatible_missed(DataReader* the_reader, const RequestedIncompatibleQosStatus& status)
	{

	}

	virtual void on_subscription_matched(DataReader* the_reader, const SubscriptionMatchedStatus& status)
	{

	}

	virtual void on_sample_lost(DataReader* the_reader, const SampleLostStatus& status)
	{

	}
};

#endif
