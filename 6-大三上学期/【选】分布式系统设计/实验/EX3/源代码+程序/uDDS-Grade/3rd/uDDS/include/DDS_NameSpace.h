#ifndef dds_namespace_h
#define dds_namespace_h

#include "BasicTypes.h"
#include "ReturnCode.h"
#include "QoSPolicy.h"
#include "DDS/DataReader.h"
//#include "datareader.h"
//#include "DDS\Listener\DataWriterListener.h"
//#include "Entity.h"
//#include "DomainParticipantFactory.h"

#define DDSTheParticipantFactory DDSDomainParticipantFactory::get_instance()
#define TheParticipantFactory DDSDomainParticipantFactory::get_instance()

	typedef long DDS_ReturnCode_t;
	const	DDS_ReturnCode_t	DDS_RETCODE_OK = 0;
	const	DDS_ReturnCode_t	DDS_RETCODE_ERROR = 1;
	const	DDS_ReturnCode_t	DDS_RETCODE_UNSUPPORTED = 2;
	const	DDS_ReturnCode_t	DDS_RETCODE_BAD_PARAMETER = 3;
	const	DDS_ReturnCode_t 	DDS_RETCODE_PRECONDITION_NOT_MET = 4;
	const	DDS_ReturnCode_t 	DDS_RETCODE_OUT_OF_RESOURCES = 5;
	const	DDS_ReturnCode_t 	DDS_RETCODE_NOT_ENABLED = 6;
	const	DDS_ReturnCode_t 	DDS_RETCODE_IMMUTABLE_POLICY = 7;
	const	DDS_ReturnCode_t 	DDS_RETCODE_INCONSISTENT_POLICY = 8;
	const	DDS_ReturnCode_t 	DDS_RETCODE_ALREADY_DELETED = 9;
	const	DDS_ReturnCode_t 	DDS_RETCODE_TIMEOUT = 10;
	const	DDS_ReturnCode_t 	DDS_RETCODE_NO_DATA = 11;
	const	DDS_ReturnCode_t 	DDS_RETCODE_ILLEGAL_OPERATION = 12;

    // ----------------------------------------------------------------------
	typedef _DOMAINID_T			DomainId_t;
	typedef DomainId_t			DDS_DomainId_t;

	typedef InstanceHandle_t	DDS_InstanceHandle_t;
	const DDS_InstanceHandle_t	DDS_HANDLE_NIL;
    typedef InstanceHandleSeq	DDS_InstanceHandleSeq;


    typedef Duration_t			DDS_Duration_t;
    typedef Time_t				DDS_Time_t;

    typedef SequenceNumber_t	DDS_SequenceNumber_t;


	typedef StatusMask DDS_StatusMask;

    //typedef StatusKind	DDS_StatusKind;
    typedef StatusMask	DDS_StatusMask;

	#define DDS_STATUS_MASK_NONE	STATUS_MASK_NONE
	#define DDS_STATUS_MASK_ALL     STATUS_MASK_ALL

    /*i deprecated */

    typedef struct SampleLostStatus DDS_SampleLostStatus;
	typedef struct RequestedDeadlineMissedStatus DDS_RequestedDeadlineMissedStatus;
	typedef struct OfferedDeadlineMissedStatus DDS_OfferedDeadlineMissedStatus;
    //typedef DDS_SampleRejectedStatusKind        SampleRejectedStatusKind;
    //typedef DDS_SampleRejectedStatus            SampleRejectedStatus;
    //typedef DDS_SampleLostStatusKind            SampleLostStatusKind;
    //typedef DDS_LivelinessLostStatus            LivelinessLostStatus;
    //typedef DDS_LivelinessChangedStatus         LivelinessChangedStatus;
    //typedef DDS_OfferedDeadlineMissedStatus     OfferedDeadlineMissedStatus;
    //typedef DDS_RequestedDeadlineMissedStatus   RequestedDeadlineMissedStatus;
    //typedef DDS_QosPolicyCount                  QosPolicyCount;
    //typedef DDS_QosPolicyCountSeq               QosPolicyCountSeq;
    //typedef DDS_OfferedIncompatibleQosStatus    OfferedIncompatibleQosStatus;
    //typedef DDS_RequestedIncompatibleQosStatus  RequestedIncompatibleQosStatus;
    //typedef DDS_PublicationMatchedStatus        PublicationMatchedStatus;
    //typedef DDS_SubscriptionMatchedStatus       SubscriptionMatchedStatus;
    //typedef DDS_ReliableReaderActivityChangedStatus  ReliableReaderActivityChangedStatus;
    //typedef DDS_ReliableWriterCacheChangedStatus     ReliableWriterCacheChangedStatus;
    //typedef DDS_ReliableWriterCacheEventCount        ReliableWriterCacheEventCount;
    //typedef DDS_DataWriterCacheStatus           DataWriterCacheStatus;
    //typedef DDS_DataWriterProtocolStatus        DataWriterProtocolStatus;
    //typedef DDS_DataReaderCacheStatus           DataReaderCacheStatus;
    //typedef DDS_DataReaderProtocolStatus        DataReaderProtocolStatus;
    //typedef DDS_ServiceRequestAcceptedStatus    ServiceRequestAcceptedStatus;
    
    // ----------------------------------------------------------------------
    // Listeners 
    // ----------------------------------------------------------------------
    typedef class DDSListener                   Listener; 
    typedef class TopicListener					DDSTopicListener;
    typedef class DataWriterListener         DDSDataWriterListener;
    typedef class PublisherListener          DDSPublisherListener;
    typedef class DataReaderListener         DDSDataReaderListener;
    typedef class SubscriberListener         DDSSubscriberListener;
    typedef class DomainParticipantListener  DDSDomainParticipantListener;
    //typedef DDS_DomainParticipantFactoryEntityListener   DomainParticipantFactoryEntityListener;

    // ----------------------------------------------------------------------
    // Conditions
    // ----------------------------------------------------------------------

    // Sample states to support reads
    typedef SampleStateKind  DDS_SampleStateKind;

    // This is a bit-mask SampleStateKind
    //typedef SampleStateMask  DDS_SampleStateMask;

    // View states to support reads
    typedef ViewStateKind    DDS_ViewStateKind;
   

    // This is a bit-mask ViewStateKind
    //typedef ViewStateMask    DDS_ViewStateMask;

    // This is a bit-mask InstanceStateKind
    //typedef InstanceStateMask DDS_InstanceStateMask;

    typedef struct SampleInfo               DDS_SampleInfo;
    typedef  SampleInfoSeq            DDS_SampleInfoSeq;


    typedef struct DomainParticipantFactoryQos  DDS_DomainParticipantFactoryQos;
    typedef struct DomainParticipantQos         DDS_DomainParticipantQos;
    typedef struct TopicQos                     DDS_TopicQos;
    typedef struct DataWriterQos                DDS_DataWriterQos;
    typedef struct PublisherQos                 DDS_PublisherQos;
    typedef struct DataReaderQos                DDS_DataReaderQos;
    typedef struct SubscriberQos                DDS_SubscriberQos;

	const  ReliabilityQosPolicyKind DDS_BEST_EFFORT_RELIABILITY_QOS = BEST_EFFORT_RELIABILITY_QOS;
	const  ReliabilityQosPolicyKind DDS_RELIABLE_RELIABILITY_QOS = RELIABLE_RELIABILITY_QOS;



    // ----------------------------------------------------------------------
#define DDS_PARTICIPANT_QOS_DEFAULT PARTICIPANT_QOS_DEFAULT
#define DDS_TOPIC_QOS_DEFAULT	TOPIC_QOS_DEFAULT
#define DDS_PUBLISHER_QOS_DEFAULT PUBLISHER_QOS_DEFAULT
#define DDS_SUBSCRIBER_QOS_DEFAULT SUBSCRIBER_QOS_DEFAULT
#define DDS_DATAWRITER_QOS_DEFAULT DATAWRITER_QOS_DEFAULT
#define DDS_DATAREADER_QOS_DEFAULT DATAREADER_QOS_DEFAULT
    //extern DDS_DLL const DDS_DomainParticipantQos &PARTICIPANT_QOS_DEFAULT;
    //extern DDS_DLL const DDS_TopicQos             &TOPIC_QOS_DEFAULT;
    //extern DDS_DLL const DDS_PublisherQos         &PUBLISHER_QOS_DEFAULT;
    //extern DDS_DLL const DDS_SubscriberQos        &SUBSCRIBER_QOS_DEFAULT;
    //extern DDS_DLL const DDS_DataWriterQos        &DATAWRITER_QOS_DEFAULT;
    //extern DDS_DLL const DDS_DataReaderQos        &DATAREADER_QOS_DEFAULT;

    //extern DDS_DLL const DDS_DataWriterQos        &DATAWRITER_QOS_USE_TOPIC_QOS;
    //extern DDS_DLL const DDS_DataReaderQos        &DATAREADER_QOS_USE_TOPIC_QOS;

    //typedef DDSEntity                    Entity;
    //typedef DDS_DomainEntity             DomainEntity;
    typedef class DomainParticipant         DDSDomainParticipant;
    typedef class DomainParticipantFactory  DDSDomainParticipantFactory;
    typedef class TypeSupport               DDSTypeSupport;
    typedef class TopicDescription          DDSTopicDescription;
    typedef class Topic                     DDSTopic;
    //typedef DDS_TopicWrapperI            TopicWrapperI;
    //typedef DDSContentFilter             ContentFilter;
    //typedef DDSContentFilteredTopic      ContentFilteredTopic;
    //typedef DDS_ContentFilteredTopicWrapperI     ContentFilteredTopicWrapperI;    
    //typedef DDSMultiTopic                MultiTopic;
    typedef class Publisher                 DDSPublisher;
    //typedef DDSPublisherSeq              PublisherSeq;
    //typedef DDSPublisher_ptr             Publisher_ptr;
    typedef class DataWriter                DDSDataWriter;
    //typedef DDSDataWriterSeq             DataWriterSeq;
    //typedef DDSDataWriter_ptr            DataWriter_ptr;
    typedef class Subscriber                DDSSubscriber;
    //typedef DDSSubscriberSeq             SubscriberSeq;
    //typedef DDSSubscriber_ptr            Subscriber_ptr;
    typedef class DataReader                DDSDataReader;
    //typedef DDSDataReaderSeq             DataReaderSeq;
    //typedef DDSDataReader_ptr            DataReader_ptr;


#endif /* ndds_namespace_cpp_h */
