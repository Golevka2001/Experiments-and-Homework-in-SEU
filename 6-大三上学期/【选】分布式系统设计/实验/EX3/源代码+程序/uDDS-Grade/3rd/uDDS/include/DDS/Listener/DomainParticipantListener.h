#pragma once

#include "DDS/Listener/DataReaderListener.h"
#include "DDS/Listener/DataWriterListener.h"

/* Nephalem 对外接口 */
class DomainParticipantListener : public DataReaderListener, public DataWriterListener
{
public:
	virtual void on_discovered_participant_data(ParticipantBuiltinTopicData& participant_data,InstanceHandle_t & participant_handle) {};

	virtual void on_subscription_data(SubscriptionBuiltinTopicData& subscription_data, const InstanceHandle_t& subscription_handle) {};

	virtual void on_publication_data(PublicationBuiltinTopicData& publication_data, const InstanceHandle_t& publication_handle) {};
};