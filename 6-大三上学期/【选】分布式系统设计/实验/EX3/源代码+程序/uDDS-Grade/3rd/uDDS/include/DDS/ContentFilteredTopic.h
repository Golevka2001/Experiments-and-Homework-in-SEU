///************************************************************
//** 文件名：ContentFilteredTopic.h
//** Copyright (c) 2011-2021 南京磐优信息科技有限公司
//** 创建人：Nephalem<250610346@qq.com>
//** 日  期：2012-07-05
//** 修改人：无
//** 日  期：无
//** 描  述：ContentFilteredTopic头文件
//** 版  本：Version 0.1
//**----------------------------------------------------------
//************************************************************/
//#ifndef CONTENTFILTEREDTOPIC_H
//#define CONTENTFILTEREDTOPIC_H
//
//#include "BasicTypes.h"
//#include "DDS/TopicDescription.h"
//#include "DDS/Topic.h"
//#include "DDS/gst.h"
//#ifdef VXWORKS
//#include <semLib.h>
//#else
//#include "Windows.h"
//#endif
//
//class Filter;
//class TypeCode;
//class ContentFilteredTopic:public TopicDescription
//{
//public:
//	ContentFilteredTopic(string strTopicName,DomainParticipant* pRelatedParticipant,
//		                 const string strFilter_Expression,Topic* pRelated_Topic,_STRING_SEQ Parameters);
//	~ContentFilteredTopic();
//	Topic* GetRelatedTopic(); //
//	//将m_pRelated_Topic的m_name,m_typeName与topicName，typeName作比较
//    bool Equal(string strTopicName, string strTypeName) 
//	{
//		return m_pRelated_Topic->Equal(strTopicName, strTypeName);
//    }
//
//	string GetRealName()
//	{
//		return m_pRelated_Topic->GetRealName();
//	}
//
//	string GetRealTypeName()
//	{
//		return m_pRelated_Topic->GetRealTypeName();
//	}
//
//	void Set_Cdr(CDR *pCdr_Data);                             //设置过滤器需要过滤的数据
//	string GetFilterExpression();
//	bool EvaluateData();
//	int GetExpressionParameters(_STRING_SEQ& StoreParameters);//将m_Expression_Parameters复制一份到StoreParameters中
//	int SetExpressionParameters(_STRING_SEQ NewParameters);//设置参数数组
//private:
//	Filter *m_pFilter;
//	Topic* m_pRelated_Topic;//相关Topic
//	string m_strFilter_Expression;//存储过滤表达式
//	_STRING_SEQ m_Expression_Parameters;//表达式参数存储
//	_ANY_DATD ParameterDistinguish(const char* pSource);//将参数数组中的string识别成具体的_ANY_DATD
//#ifdef VXWORKS   //移植
//	SEM_ID m_hSemMutex;
//#else
//	HANDLE m_hSemMutex;
//#endif
//};
//#endif