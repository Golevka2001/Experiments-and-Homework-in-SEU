/************************************************************
** 文件名：ReturnCode.h
** Copyright (c) 2011-2021 南京磐优信息科技有限公司
** 创建人：Nephalem<250610346@qq.com>
** 日  期：2011-01-11
** 修改人：无
** 日  期：无
** 描  述：ReturnCode头文件
** 版  本：Version 0.1
**----------------------------------------------------------
************************************************************/
#ifndef _DDS_RETURNCODE_H_INCLUDED_
#define _DDS_RETURNCODE_H_INCLUDED_

typedef long ReturnCode_t;
typedef long ReturnCode_t;
typedef ReturnCode_t _RETURNCODE_T;
const	ReturnCode_t	RETCODE_OK = 0;
const	ReturnCode_t	RETCODE_ERROR = 1;
const	ReturnCode_t	RETCODE_UNSUPPORTED = 2;
const	ReturnCode_t	RETCODE_BAD_PARAMETER = 3;
const	ReturnCode_t 	RETCODE_PRECONDITION_NOT_MET = 4;
const	ReturnCode_t 	RETCODE_OUT_OF_RESOURCES = 5;
const	ReturnCode_t 	RETCODE_NOT_ENABLED = 6;
const	ReturnCode_t 	RETCODE_IMMUTABLE_POLICY = 7;
const	ReturnCode_t 	RETCODE_INCONSISTENT_POLICY = 8;
const	ReturnCode_t 	RETCODE_ALREADY_DELETED = 9;
const	ReturnCode_t 	RETCODE_TIMEOUT = 10;
const	ReturnCode_t 	RETCODE_NO_DATA = 11;
const	ReturnCode_t 	RETCODE_ILLEGAL_OPERATION = 12;


/**
* @ DomainParticipant ReturnCode
*/
//配置项失败
const ReturnCode_t RETURNCODE_CONFIG_FAILED = -101;
//Locator初始化失败（ip错误）
const ReturnCode_t RETURNCODE_LOCATOR_INIT_FAILED = -102;
//删除Reader时Reader不存在
const ReturnCode_t RETURNCODE_READER_NOT_EXIST = -103;
//删除Writer时Writer不存在
const ReturnCode_t RETURNCODE_WRITER_NOT_EXIST = -104;
//SEND任务创建失败
const ReturnCode_t RETURNCODE_SENDTASK_CREATE_FAILED = -105;
//RECEIVE任务创建失败
const ReturnCode_t RETURNCODE_RECEIVETASK_CREATE_FAILED = -106;
//DISPATCH任务创建失败
const ReturnCode_t RETURNCODE_DISPATCHTASK_CREATE_FAILED = -107;
//2015-3-18 hjy add:check multi network card IP address in the ddsconfig.conf is right or not
const ReturnCode_t RETURNCODE_MULTI_NETWORK_CARD_IP_NOT_EXIST = -108;

/**
* @ Participant ReturnCode
*/
const ReturnCode_t RETURNCODE_PARTICIPANT_CREATE_FAILED = 2;


/**
* @ HistoryCache ReturnCode
*/
const ReturnCode_t RETURNCODE_CACHE_FULL = 3;
const ReturnCode_t RETURNCODE_CACHE_EMPTY = 4;
const ReturnCode_t RETURNCODE_CHANGE_RE_ADD = 5;
const ReturnCode_t RETURNCODE_CHANGE_NOT_EXIST = 6;
const ReturnCode_t RETURNCODE_CACHE_INIT_FAILED = 7;

/**
* @ ReceiveBuffer ReturnCode
*/
const ReturnCode_t RETURNCODE_BUFFER_EMPTY = 7;
const ReturnCode_t RETURNCODE_BUFFER_FULL = 8;
const ReturnCode_t RETURNCODE_RECVBUFFER_ERROR = 9;

/**
* @ MessageTransmitter ReturnCode
*/
const ReturnCode_t RETURNCODE_ADDR_RE_ADD = 9;
const ReturnCode_t RETURNCODE_ADDR_NOT_EXIST = 10;


/**
* @ Writer/StatefulWriter ReturnCode
*/
const ReturnCode_t RETURNCODE_READERPROXY_NOT_EXIST = 200;
const ReturnCode_t RETURNCODE_STATEFULWRITER_INIT_FAILED = 995;
const ReturnCode_t RETURNCODE_NO_DATA_TO_SEND = 222;

/**
* @ Reader/StatefulReader ReturnCode
*/
const ReturnCode_t RETURNCODE_STATEFULREADER_INIT_FAILED = 990;
const ReturnCode_t RETURNCODE_READER_INIT_FAILED = 989;
const ReturnCode_t RETURNCODE_NEW_CHANGE_FAILED = 12;
const ReturnCode_t RETURNCODE_DATA_MESSAGE_INVALID = 13;
const ReturnCode_t RETURNCODE_NO_MATCHED_WRITERPROXY = 14;
const ReturnCode_t RETURNCODE_HEARTBEAT_TOO_SOON = 2;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_RE_ADD = 15;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_NOT_EXIST = 16;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_NOTIFY_ERROR = 17;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_LOST_UPDATE_ERROR = 18;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_MISSING_UPDATE_ERROR = 19;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_RECEIVED_AGAIN = 20;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_RECEIVED_REJECT = 21;
const ReturnCode_t RETURNCODE_CHANGE_FROM_WRITER_RECEIVED_SET_ERROR =22;

/**
* @ WriterProxy ReturnCode
*/
const ReturnCode_t RETURNCODE_WRITERPROXY_RE_ADD = 23;
const ReturnCode_t RETURNCODE_WRITERPROXY_NOT_EXIST = 24;

/**
* @ ReaderProxy ReturnCode
*/
const ReturnCode_t RETURNCODE_CHANGEFORREADER_NOT_EXIST = 1000;
const ReturnCode_t RETURNCODE_READERPROXY_INIT_FAILED = 10000;


//接收的Data报文不含数据
const ReturnCode_t RETURNCODE_DATA_EMPTY = 25;

const ReturnCode_t RETURNCODE_DATA_NOTIFY_FAILED = 26;


const ReturnCode_t RETURNCODE_REQUEST_ERROR = 27;

const ReturnCode_t RETURNCODE_ENDPOINT_NOT_EXIST = 28;
const ReturnCode_t RETURNCODE_SUBMESSAGE_INVALID = 29;

//const ReturnCode_t RETCODE_ERROR = -1;
const ReturnCode_t RETURNCODE_ACKNACK_GET_ERROR = 30;



//
const ReturnCode_t RETURN_DEADLINE_MISSED = 2;


const ReturnCode_t RETURNCODE_CLEAN_SUCCESSFUL = 31;
const ReturnCode_t RETURNCODE_INITIALIZE_SUCCESSFUL = 32;
const ReturnCode_t RETURNCODE_DELETE_FAIL = 33;
const ReturnCode_t RETURNCODE_DELETE_SUCCESSFUL = 34;
const ReturnCode_t RETURNCODE_REGISTER_TYPE_EXISTED= 35;
const ReturnCode_t RETURNCODE_ADD_SUCCESSFUL= 36;
const ReturnCode_t RETURNCODE_REPLACE_SUCCESSFUL= 37;
const ReturnCode_t RETURNCODE_REPLACE_FAIL= 38;
const ReturnCode_t RETURNCODE_REGISTER_TYPECODE_EXISTED= 39;


/**
* @ DataReader ReturnCode
*/
const ReturnCode_t RETURNCODE_SET_QOS_DISCOVERY_MODIFY_FAILED= 38;
const ReturnCode_t RETURNCODE_SET_LISTENER_DISCOVERY_MODIFY_FAILED= 38;
const ReturnCode_t RETURNCODE_GET_CHANGE_FAILED= 38;
const ReturnCode_t RETURNCODE_ON_DATA_AVAILABLE_ERROR= 38;
const ReturnCode_t RETURNCODE_NO_SAMPLE= 38;
const ReturnCode_t RETURNCODE_ON_REQUESTED_DEADLINE_MISSED= 38;

/**
* @ DataWriter ReturnCode
*/
//const ReturnCode_t RETURNCODE_REMOVE_CHANGE_FAILED= 38;
//const ReturnCode_t RETURNCODE_ON_OFFERED_DEADLINE_MISSED= 38;
const ReturnCode_t RETURNCODE_NEW_CACHECHANGE_FAILED= 38;
const ReturnCode_t RETURNCODE_ADD_CHANGE_FAILED= 38;
const ReturnCode_t RETURNCODE_SEND_DATA_FAILED= 38;

/**
* @ DomainParticipantFactory ReturnCode
*/
const ReturnCode_t RETURNCODE_NO_DOMAINID= 38;
const ReturnCode_t RETURNCODE_DELETE_PARTICIPANT_FAILED= 38;
const ReturnCode_t RETURNCODE_NO_DOMAINPARTICIPANT= 38;



/**
* @ StringDataReader ReturnCode
*/

//const ReturnCode_t RETURNCODE_DELETE_SAMPLEINFO_FAILED= 38;




const ReturnCode_t lReturnCode_tRANSMITTERUNICAST_FAIDED = 50;

const ReturnCode_t RETURNCODE_SEND_FAIDED = 51;
const ReturnCode_t RETURNCODE_RECEIVE_ADDR_ADD_ERROR = 52;
//StringTypeSupport

const ReturnCode_t RETURNCODE_SOURCE_ADDR_NOT_EXIST = 53;

const ReturnCode_t RETURNCODE_RIGISTER_TYPE_FAILED= 38;
const ReturnCode_t RETURNCODE_REUSEADDR_ERROR = 50;
const ReturnCode_t RETURNCODE_REUSEPORT_ERROR = 51;
const ReturnCode_t RETURNCODE_RECEFROM_FAILED = 56;
const ReturnCode_t RETURNCODE_SELECT_ERROR = 57;
const ReturnCode_t RETURNCODE_SELECT_TIMEOUT = 58;

const ReturnCode_t RETURNCODE_RECEIVE_ADDR_EMPTY = 100;

const ReturnCode_t RETURNCODE_REQUEST_NO_LONGER_EXIST = 110;


const ReturnCode_t RETURNCODE_BORADCAST_ERROR = 120;


const ReturnCode_t RETURNCODE_REGISTER_TYPE_NULL = 130;

const ReturnCode_t RETURNCODE_AGENT_INIT_FAILED = 140;
const ReturnCode_t RETURNCODE_REGISTER_TYPE_NOT_EXSIT = 150;
const ReturnCode_t RETURNCODE_DOMAIN_PARTICIPANT_CREATE_FAILED = 160;

const ReturnCode_t RETURNCODE_DOMAIN_NOT_INIT = 500;
const ReturnCode_t RETURNCODE_DOMAIN_INIT_FAILED = 600;


const ReturnCode_t RETURNCODE_SENDPARTICIPANTDATA_FAILED = 800;

const ReturnCode_t RETURNCODE_PARTICIPANT_LISTENER_ERROR = 900;
const ReturnCode_t RETURNCODE_CHECKTASK_CREATE_FAILED = 1000;

const ReturnCode_t RETURNCODE_ACK_ENCAPSULATE_ERROR = 5436;
const ReturnCode_t RETURNCODE_ACK_LOCATOR_ERROR = 554;
const ReturnCode_t RETURNCODE_DATA_ENCAPSULATE_ERROR = 567;
const ReturnCode_t RETURNCODE_DATA_LOCATOR_ERROR = 645;
const ReturnCode_t RETURNCODE_CREATE_DATAWRITER_FAILED = 999;
const ReturnCode_t RETURNCODE_CREATE_DATAREADER_FAILED = 998;

const ReturnCode_t RETURNCODE_DELETEREQUEST_NOT_EXIST = 997;



const ReturnCode_t RETURNCODE_HEARTBEAT_GET_ERROR = 900;

const ReturnCode_t RETURNCODE_DATA_GET_ERROR = 143;


const ReturnCode_t RETURNCODE_PARTICIPANT_DATAMANAGER_INIT_FAILED = 953;
const ReturnCode_t RETURNCODE_PUBLICATIONS_DATAMANAGER_INIT_FAILED = 957;
const ReturnCode_t RETURNCODE_SUBSCRIPTIONS_DATAMANAGER_INIT_FAILED = 956;


const ReturnCode_t RETURNCODE_APPSET_FAILED = 1111;

const ReturnCode_t RETURNCODE_APP_NOTSET = 1241;

const ReturnCode_t RETURNCODE_RECORDSEND_ERROR = 1241;

const ReturnCode_t RETURNCODE_DOMAINPARTICIPANT_BUILTINENDPOINT_INIT_FAILED = 12412;

const ReturnCode_t RETURNCODE_DISCOVERY_PARTICIPANTDATAWRITER_CREATE_FAILED = 242;
const ReturnCode_t RETURNCODE_DISCOVERY_PUBLICATIONSDATAWRITER_CREATE_FAILED = 4124;
const ReturnCode_t RETURNCODE_DISCOVERY_SUBSCRIPTIONSDATAWRITER_CREATE_FAILED = 214;
const ReturnCode_t RETURNCODE_DISCOVERY_PARTICIPANTDATAREADER_CREATE_FAILED = 24;
const ReturnCode_t RETURNCODE_DISCOVERY_PUBLICATIONSDATAREADER_CREATE_FAILED = 241;
const ReturnCode_t RETURNCODE_DISCOVERY_SUBSCRIPTIONSDATAREADER_CREATE_FAILED = 215;

/**
* @ KeyedStringDataWriter ReturnCode
*/
const ReturnCode_t RETURNCODE_BAD_PARAMETER = 201;
const ReturnCode_t RETURNCODE_PRECONDITION_NOT_MET = 202;
const ReturnCode_t RETURNCODE_NO_DATA = 203;

/**
* @ Multicast ReturnCode
*/
const ReturnCode_t RETURNCODE_MULTIADDRESS_ERROR = 1250;
const ReturnCode_t RETURNCODE_MULTICAST_ERROR = 1251;
const ReturnCode_t RETURNCODE_RECEIVE_MULTIADDR_ADD_ERROR = 1252;
const ReturnCode_t RETURNCODE_MULTIGROUP_QUIT_ERROR = 1253;

/**
* @ Multicast ReturnCode
*/
const ReturnCode_t RETURNCODE_FRAGMISSING = 1260;

/**
* @ Delete DataWriter/DataReader ReturnCode
*/
const ReturnCode_t RETURNCODE_DELETEDATAWRITER_OK = 1270;
const ReturnCode_t RETURNCODE_DELETEDATAREADER_OK = 1271;

const ReturnCode_t RETURNCODE_NO_MEMORY = 230;

#endif
