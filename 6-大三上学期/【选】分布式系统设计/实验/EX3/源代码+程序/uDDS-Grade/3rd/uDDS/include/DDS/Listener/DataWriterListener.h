/************************************************************
** 文件名：DataWriterListener.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-20
** 修改人：无
** 日  期：无
** 描  述：DataWriterListener头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_DATAWRITERLISTENER_H_INCLUDED_
#define _DDS_DATAWRITERLISTENER_H_INCLUDED_
#include "BasicTypes.h"
#include "ReturnCode.h"
#include "DDS/Listener/DDSListener.h"

class DataReader;
class DataWriter;

struct LivelinessLostStatus
{
	/*e \dref_LivelinessLostStatus_total_count
	 */
	int total_count;

	/*e \dref_LivelinessLostStatus_total_count_change
	 */
	int total_count_change;
};

struct OfferedDeadlineMissedStatus {
	/*e \dref_OfferedDeadlineMissedStatus_total_count
	 */
	int total_count;

	/*e \dref_OfferedDeadlineMissedStatus_total_count_change
	 */
	int total_count_change;

	/*e \dref_OfferedDeadlineMissedStatus_last_instance_handle
	 */
	//DDS_InstanceHandle_t last_instance_handle;
};

struct OfferedIncompatibleQosStatus {
	/*e \dref_OfferedIncompatibleQosStatus_total_count
	 */
	int total_count;

	/*e \dref_OfferedIncompatibleQosStatus_total_count_change
	 */
	int total_count_change;

	/*e \dref_OfferedIncompatibleQosStatus_last_policy_id
	 */
	QosPolicyId_t last_policy_id;

	/*e \dref_OfferedIncompatibleQosStatus_policies
	 */
	//struct QosPolicyCountSeq policies;
};

struct PublicationMatchedStatus 
{
	int total_count;

	int total_count_change;

	int current_count;

	int current_count_peak;

	int current_count_change;

	InstanceHandle_t last_subscription_handle;
};

class DataWriterListener : DDSListener 
{
public:
    DataWriterListener() {}

    virtual ~DataWriterListener() {}

	virtual void on_liveliness_lost(DataWriter* the_writer, const LivelinessLostStatus& Status)
	{
	}

    virtual void on_offered_deadline_missed(DataWriter* the_writer, const OfferedDeadlineMissedStatus& Status)
    {	
    }

	virtual void on_offered_incompatible_qos(DataWriter* the_writer, const OfferedIncompatibleQosStatus& Status)
	{
	}

	virtual void on_publication_matched(DataWriter* the_writer, const PublicationMatchedStatus& Status)
	{
	}



};

#endif
