#pragma once
#include "BasicTypes.h"

#include <string>
using std::string;

const  string  USERDATA_QOS_POLICY_NAME				= "UserData";
const  string  DURABILITY_QOS_POLICY_NAME			= "Durability";
const  string  PRESENTATION_QOS_POLICY_NAME			= "Presentation";
const  string  DEADLINE_QOS_POLICY_NAME				= "Deadline";
const  string  LATENCYBUDGET_QOS_POLICY_NAME		= "LatencyBudget";
const  string  OWNERSHIP_QOS_POLICY_NAME			= "Ownership";
const  string  OWNERSHIPSTRENGTH_QOS_POLICY_NAME	= "OwnershipStrength";
const  string  LIVELINESS_QOS_POLICY_NAME			= "Liveliness";
const  string  TIMEBASEDFILTER_QOS_POLICY_NAME		= "TimeBasedFilter";
const  string  PARTITION_QOS_POLICY_NAME			= "Partition";
const  string  RELIABILITY_QOS_POLICY_NAME			= "Reliability";
const  string  DESTINATIONORDER_QOS_POLICY_NAME		= "DestinationOrder";
const  string  HISTORY_QOS_POLICY_NAME				= "History";
const  string  RESOURCELIMITS_QOS_POLICY_NAME		= "ResourceLimits";
const  string  ENTITYFACTORY_QOS_POLICY_NAME		= "EntityFactory";
const  string  WRITERDATALIFECYCLE_QOS_POLICY_NAME	= "WriterDataLifecycle";
const  string  READERDATALIFECYCLE_QOS_POLICY_NAME	= "ReaderDataLifecycle";
const  string  TOPICDATA_QOS_POLICY_NAME			= "TopicData";
const  string  GROUPDATA_QOS_POLICY_NAME			= "TransportPriority";
const  string  LIFESPAN_QOS_POLICY_NAME				= "Lifespan";
const  string  DURABILITYSERVICE_POLICY_NAME		= "DurabilityService";

typedef long QosPolicyId_t;
const  QosPolicyId_t  INVALID_QOS_POLICY_ID = 0;
const  QosPolicyId_t  USERDATA_QOS_POLICY_ID = 1;
const  QosPolicyId_t  DURABILITY_QOS_POLICY_ID = 2;
const  QosPolicyId_t  PRESENTATION_QOS_POLICY_ID = 3;
const  QosPolicyId_t  DEADLINE_QOS_POLICY_ID = 4;
const  QosPolicyId_t  LATENCYBUDGET_QOS_POLICY_ID = 5;
const  QosPolicyId_t  OWNERSHIP_QOS_POLICY_ID = 6;
const  QosPolicyId_t  OWNERSHIPSTRENGTH_QOS_POLICY_ID = 7;
const  QosPolicyId_t  LIVELINESS_QOS_POLICY_ID = 8;
const  QosPolicyId_t  TIMEBASEDFILTER_QOS_POLICY_ID = 9;
const  QosPolicyId_t  PARTITION_QOS_POLICY_ID = 10;
const  QosPolicyId_t  RELIABILITY_QOS_POLICY_ID = 11;
const  QosPolicyId_t  DESTINATIONORDER_QOS_POLICY_ID = 12;
const  QosPolicyId_t  HISTORY_QOS_POLICY_ID = 13;
const  QosPolicyId_t  RESOURCELIMITS_QOS_POLICY_ID = 14;
const  QosPolicyId_t  ENTITYFACTORY_QOS_POLICY_ID = 15;
const  QosPolicyId_t  WRITERDATALIFECYCLE_QOS_POLICY_ID = 16;
const  QosPolicyId_t  READERDATALIFECYCLE_QOS_POLICY_ID = 17;
const  QosPolicyId_t  TOPICDATA_QOS_POLICY_ID = 18;
const  QosPolicyId_t  GROUPDATA_QOS_POLICY_ID = 19;
const  QosPolicyId_t  TRANSPORTPRIORITY_QOS_POLICY_ID = 20;
const  QosPolicyId_t  LIFESPAN_QOS_POLICY_ID = 21;
const  QosPolicyId_t  DURABILITYSERVICE_QOS_POLICY_ID = 22;

const unsigned int LENGTH_UNLIMITED = -1;


struct UserDataQosPolicy
{
	sequence<octet>  value;
};

struct TopicDataQosPolicy
{
	sequence<octet>  value;
};

struct GroupDataQosPolicy
{
	sequence<octet>  value;
};

struct TransportPriorityQosPolicy
{
	unsigned int			value;

	TransportPriorityQosPolicy() : value(0)
	{
	};
};
struct LifespanQosPolicy
{
	Duration_t	duration;

	LifespanQosPolicy() :duration(TIME_INFINITE)
	{

	};
};

enum DurabilityQosPolicyKind
{
	/* Nephalem 默认属性，没有订阅者时数据不会缓存 */
	VOLATILE_DURABILITY_QOS,
	/* Nephalem 没有订阅者也会缓存数据，数量有history控制 */
	/* Nephalem 目前只对发布方有实际效果 */
	TRANSIENT_LOCAL_DURABILITY_QOS,
	/* Nephalem 可选，数据缓存不受DataWriter生命周期影响 */
	TRANSIENT_DURABILITY_QOS,
	/* Nephalem 可选，数据保存在硬盘中 */
	PERSISTENT_DURABILITY_QOS
};

struct DurabilityQosPolicy
{
	DurabilityQosPolicyKind  kind;

	DurabilityQosPolicy() :kind(VOLATILE_DURABILITY_QOS) {};
};
enum PresentationQosPolicyAccessScopeKind
{
	INSTANCE_PRESENTATION_QOS,
	TOPIC_PRESENTATION_QOS,
	GROUP_PRESENTATION_QOS
};
struct PresentationQosPolicy
{
	PresentationQosPolicyAccessScopeKind	access_scope;
	bool 									coherent_access;
	bool 									ordered_access;

	PresentationQosPolicy() :access_scope(INSTANCE_PRESENTATION_QOS), coherent_access(0), ordered_access(0)
	{

	};
};

struct DeadlineQosPolicy
{
	Duration_t	period;

	DeadlineQosPolicy() : period(TIME_INFINITE)
	{

	};
};

struct LatencyBudgetQosPolicy
{
	Duration_t	duration;

	LatencyBudgetQosPolicy() : duration(TIME_INFINITE)
	{

	};
};

enum OwnershipQosPolicyKind
{
	SHARED_OWNERSHIP_QOS,
	EXCLUSIVE_OWNERSHIP_QOS
};

struct OwnershipQosPolicy
{
	OwnershipQosPolicyKind	kind;

	OwnershipQosPolicy():kind(SHARED_OWNERSHIP_QOS)
	{

	}
};

struct OwnershipStrengthQosPolicy
{
	unsigned int		value;

	OwnershipStrengthQosPolicy() :value(0)
	{

	};
};
enum LivelinessQosPolicyKind
{
	AUTOMATIC_LIVELINESS_QOS,
	MANUAL_BY_PARTICIPANT_LIVELINESS_QOS,
	MANUAL_BY_TOPIC_LIVELINESS_QOS
};

struct LivelinessQosPolicy
{
	LivelinessQosPolicyKind		kind;
	Duration_t 					lease_duration;

	LivelinessQosPolicy() : kind(AUTOMATIC_LIVELINESS_QOS), lease_duration(TIME_INFINITE)
	{

	};
};

struct TimeBasedFilterQosPolicy
{
	Duration_t					minimum_separation;

	TimeBasedFilterQosPolicy() : minimum_separation(TIME_ZERO)
	{

	};
};
struct PartitionQosPolicy
{
	StringSeq						name;
};

enum ReliabilityQosPolicyKind
{
	BEST_EFFORT_RELIABILITY_QOS = 1,
	RELIABLE_RELIABILITY_QOS
};

struct ReliabilityQosPolicy
{
	ReliabilityQosPolicyKind 		kind;
	Duration_t 					max_blocking_time;

	ReliabilityQosPolicy()
	{
		this->kind = BEST_EFFORT_RELIABILITY_QOS;
	}
};

enum DestinationOrderQosPolicyKind
{
	BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS,
	BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS
};

struct DestinationOrderQosPolicy
{
	DestinationOrderQosPolicyKind	kind;

	DestinationOrderQosPolicy() : kind(BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS)
	{

	};
};

enum HistoryQosPolicyKind
{
	KEEP_LAST_HISTORY_QOS,
	KEEP_ALL_HISTORY_QOS
};

struct HistoryQosPolicy
{
	HistoryQosPolicyKind			kind;
	unsigned int 					depth;

	HistoryQosPolicy()
	{
		kind = KEEP_LAST_HISTORY_QOS;
		depth = 1;
	}
};

struct ResourceLimitsQosPolicy
{
	unsigned int 				max_samples;
	unsigned int 				max_instances;
	unsigned int 				max_samples_per_instance;

	
	ResourceLimitsQosPolicy()
	{
		max_samples = LENGTH_UNLIMITED;
		max_instances = LENGTH_UNLIMITED;
		max_samples_per_instance = LENGTH_UNLIMITED;
	}
};

struct EntityFactoryQosPolicy
{
	bool 					autoenable_created_entities;

	EntityFactoryQosPolicy() :autoenable_created_entities(true)
	{

	};
};

struct WriterDataLifecycleQosPolicy
{
	bool 					autodispose_unregistered_instances;

	WriterDataLifecycleQosPolicy() :autodispose_unregistered_instances(true)
	{

	};
};

struct ReaderDataLifecycleQosPolicy
{
	Duration_t 					autopurge_nowriter_samples_delay;
	Duration_t 					autopurge_disposed_samples_delay;

	ReaderDataLifecycleQosPolicy() :
		autopurge_nowriter_samples_delay(TIME_INFINITE),
		autopurge_disposed_samples_delay(TIME_INFINITE)
	{

	}
};

struct DurabilityServiceQosPolicy
{
	Duration_t 					service_cleanup_delay;
	HistoryQosPolicyKind 		history_kind;
	unsigned int 				history_depth;
	unsigned int 				max_samples;
	unsigned int 				max_instances;
	unsigned int 				max_samples_per_instance;

	DurabilityServiceQosPolicy() :
		service_cleanup_delay(TIME_ZERO),
		history_kind(KEEP_ALL_HISTORY_QOS),
		history_depth(1),
		max_samples(LENGTH_UNLIMITED),
		max_instances(LENGTH_UNLIMITED),
		max_samples_per_instance(LENGTH_UNLIMITED)
	{

	}
};
enum TransportMulticastQosPolicyKind 
{
	DDS_AUTOMATIC_TRANSPORT_MULTICAST_QOS,

	DDS_UNICAST_ONLY_TRANSPORT_MULTICAST_QOS

} ;


struct TransportMulticastSettings
{
	///*e \dref_TransportMulticastSettings_t_transports
	//*/
	//struct DDS_StringSeq transports;

	char* receive_address;

	unsigned int  receive_port;

	TransportMulticastSettings()
	{
		receive_address = NULL;

		receive_port = 0;
	}

};

typedef sequence<TransportMulticastSettings> TransportMulticastSettingsSeq;

struct TransportMulticastQosPolicy
{

	TransportMulticastQosPolicyKind kind;

	TransportMulticastSettingsSeq value;

	TransportMulticastQosPolicy()
	{
		kind = DDS_UNICAST_ONLY_TRANSPORT_MULTICAST_QOS;
	}
};

struct DomainParticipantFactoryQos
{
	//EntityFactoryQosPolicy 		entity_factory;
};

struct DomainParticipantQos
{
	UserDataQosPolicy 			user_data;
	EntityFactoryQosPolicy 		entity_factory;

	/* Nephalem 自定义接口 */

	/* Nephalem 兼容RTI，设置组播接收地址*/
	TransportMulticastQosPolicy multicast;

	const char* local_ip;

	DomainParticipantQos()
	{
		local_ip = NULL;
	}
};

struct TopicQos
{
	TopicDataQosPolicy			topic_data;
	DurabilityQosPolicy 		durability;
	DurabilityServiceQosPolicy 	durability_service;
	DeadlineQosPolicy 			deadline;
	LatencyBudgetQosPolicy		latency_budget;
	LivelinessQosPolicy 		liveliness;
	ReliabilityQosPolicy 		reliability;
	DestinationOrderQosPolicy 	destination_order;
	HistoryQosPolicy 			history;
	ResourceLimitsQosPolicy 	resource_limits;
	TransportPriorityQosPolicy 	transport_priority;
	LifespanQosPolicy 			lifespan;
	OwnershipQosPolicy 			ownership;
};

struct DataWriterQos
{
	DurabilityQosPolicy 			durability;
	DurabilityServiceQosPolicy 	durability_service;
	DeadlineQosPolicy 			deadline;
	LatencyBudgetQosPolicy 		latency_budget;
	LivelinessQosPolicy 			liveliness;
	ReliabilityQosPolicy 			reliability;
	DestinationOrderQosPolicy 	destination_order;
	HistoryQosPolicy 			history;
	ResourceLimitsQosPolicy 		resource_limits;
	TransportPriorityQosPolicy 	transport_priority;
	LifespanQosPolicy 			lifespan;
	UserDataQosPolicy 			user_data;
	OwnershipQosPolicy 		ownership;
	OwnershipStrengthQosPolicy 	ownership_strength;
	WriterDataLifecycleQosPolicy 	writer_data_lifecycle;
};

struct PublisherQos
{
	PresentationQosPolicy 		presentation;
	PartitionQosPolicy 			partition;
	GroupDataQosPolicy 			group_data;
	EntityFactoryQosPolicy 		entity_factory;
};

struct DataReaderQos
{
	DurabilityQosPolicy 			durability;
	DeadlineQosPolicy 			deadline;
	LatencyBudgetQosPolicy 		latency_budget;
	LivelinessQosPolicy 			liveliness;
	ReliabilityQosPolicy 			reliability;
	DestinationOrderQosPolicy 	destination_order;
	HistoryQosPolicy 			history;
	ResourceLimitsQosPolicy 		resource_limits;
	UserDataQosPolicy 			user_data;
	OwnershipQosPolicy 		ownership;
	TimeBasedFilterQosPolicy 	time_based_filter;
	ReaderDataLifecycleQosPolicy	reader_data_lifecycle;

	/* Nephalem 兼容RTI，设置组播接收地址*/
	TransportMulticastQosPolicy multicast;
};

struct SubscriberQos
{
	PresentationQosPolicy 		presentation;
	PartitionQosPolicy 			partition;
	GroupDataQosPolicy 		group_data;
	EntityFactoryQosPolicy		entity_factory;
};



struct TopicBuiltinTopicData
{
	//BuiltinTopicKey_t 			key;
	//string 						name;
	//string 						type_name;
	//DurabilityQosPolicy 			durability;
	//DurabilityServiceQosPolicy 	durability_service;
	//DeadlineQosPolicy 			deadline;
	//LatencyBudgetQosPolicy 		latency_budget;
	//LivelinessQosPolicy 			liveliness;
	//ReliabilityQosPolicy 			reliability;
	//TransportPriorityQosPolicy 	transport_priority;
	//LifespanQosPolicy 			lifespan;
	//DestinationOrderQosPolicy 	destination_order;
	//HistoryQosPolicy 			history;
	//ResourceLimitsQosPolicy 		resource_limits;
	//OwnershipQosPolicy			ownership;
	//TopicDataQosPolicy 			topic_data;
};

//#define PARTICIPANT_QOS_DEFAULT
//#define TOPIC_QOS_DEFAULT
//#define PUBLISHER_QOS_DEFAULT
//#define SUBSCRIBER_QOS_DEFAULT
//#define DATAWRITER_QOS_DEFAULT
//#define DATAREADER_QOS_DEFAULT
//#define DATAWRITER_QOS_USE_TOPIC_QOS
//#define DATAREADER_QOS_USE_TOPIC_QOS

const DomainParticipantQos PARTICIPANT_QOS_DEFAULT;
const TopicQos TOPIC_QOS_DEFAULT;
const PublisherQos PUBLISHER_QOS_DEFAULT;
const SubscriberQos SUBSCRIBER_QOS_DEFAULT;
const DataWriterQos DATAWRITER_QOS_DEFAULT;
const DataReaderQos DATAREADER_QOS_DEFAULT;


/* Nephalem 为了与RTI兼容，和RTPS规范并不是完全一致*/
struct ParticipantProxy
{
	ProtocolVersion_t		rtps_protocol_version;
	guidPrefix_t			guidPrefix;
	VendorId_t				rtps_vendor_id;
	bool					expectsInlineQos;
	BuiltinEndpointSet_t	dds_builtin_endpoints;
	/* Nephalem SEPD地址 */
	_LOCATOR_LIST_T			metatraffic_unicast_locators;
	/* Nephalem SPDP组播发现地址 默认为239.255.0.1 */
	_LOCATOR_LIST_T			metatraffic_multicast_locators;
	/* Nephalem 用户数据相关默认单播地址 */
	_LOCATOR_LIST_T			default_unicast_locators;
	_LOCATOR_LIST_T			defaultMulticastLocatorList;
	Count_t					manualLivelinessCount;

	Duration_t					lease_duration;

	/* Nephalem 新增*/
	/* Nephalem 为了作为map的key，新增GUID_t,方便查找 EntityID固定为ENTITYID_PARTICIPANT*/
	GUID_t				participantDataWriterGuid;

	ParticipantProxy()
	{
		participantDataWriterGuid.entityId = ENTITYID_PARTICIPANT;
	}
};

struct ParticipantBuiltinTopicData : ParticipantProxy
{
	BuiltinTopicKey_t 			key;
	UserDataQosPolicy 			user_data;
};


struct SubscriptionBuiltinTopicData
{
	BuiltinTopicKey_t 				key;
	BuiltinTopicKey_t 				participant_key;
	string 							topic_name;
	string 							type_name;
	DurabilityQosPolicy 			durability;
	DeadlineQosPolicy 				deadline;
	LatencyBudgetQosPolicy 			latency_budget;
	LivelinessQosPolicy 			liveliness;
	ReliabilityQosPolicy 			reliability;
	OwnershipQosPolicy 				ownership;
	DestinationOrderQosPolicy 		destination_order;
	UserDataQosPolicy 				user_data;
	TimeBasedFilterQosPolicy 		time_based_filter;
	PresentationQosPolicy 			presentation;
	PartitionQosPolicy 				partition;
	TopicDataQosPolicy 				topic_data;
	GroupDataQosPolicy 				group_data;
};

struct PublicationBuiltinTopicData
{
	BuiltinTopicKey_t 				key;
	BuiltinTopicKey_t 				participant_key;
	string 							topic_name;
	string 							type_name;
	DurabilityQosPolicy 			durability;
	DurabilityServiceQosPolicy		durability_service;
	DeadlineQosPolicy 				deadline;
	LatencyBudgetQosPolicy 			latency_budget;
	LivelinessQosPolicy 			liveliness;
	ReliabilityQosPolicy 			reliability;
	LifespanQosPolicy 				lifespan;
	UserDataQosPolicy 				user_data;
	OwnershipQosPolicy 				ownership;
	OwnershipStrengthQosPolicy 		ownership_strength;
	DestinationOrderQosPolicy 		destination_order;
	PresentationQosPolicy 			presentation;
	PartitionQosPolicy 				partition;
	TopicDataQosPolicy 				topic_data;
	GroupDataQosPolicy 				group_data;
};