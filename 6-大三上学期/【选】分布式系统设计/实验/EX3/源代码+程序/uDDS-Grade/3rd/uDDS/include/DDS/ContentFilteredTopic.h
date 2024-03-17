///************************************************************
//** �ļ�����ContentFilteredTopic.h
//** Copyright (c) 2011-2021 �Ͼ�������Ϣ�Ƽ����޹�˾
//** �����ˣ�Nephalem<250610346@qq.com>
//** ��  �ڣ�2012-07-05
//** �޸��ˣ���
//** ��  �ڣ���
//** ��  ����ContentFilteredTopicͷ�ļ�
//** ��  ����Version 0.1
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
//	//��m_pRelated_Topic��m_name,m_typeName��topicName��typeName���Ƚ�
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
//	void Set_Cdr(CDR *pCdr_Data);                             //���ù�������Ҫ���˵�����
//	string GetFilterExpression();
//	bool EvaluateData();
//	int GetExpressionParameters(_STRING_SEQ& StoreParameters);//��m_Expression_Parameters����һ�ݵ�StoreParameters��
//	int SetExpressionParameters(_STRING_SEQ NewParameters);//���ò�������
//private:
//	Filter *m_pFilter;
//	Topic* m_pRelated_Topic;//���Topic
//	string m_strFilter_Expression;//�洢���˱��ʽ
//	_STRING_SEQ m_Expression_Parameters;//���ʽ�����洢
//	_ANY_DATD ParameterDistinguish(const char* pSource);//�����������е�stringʶ��ɾ����_ANY_DATD
//#ifdef VXWORKS   //��ֲ
//	SEM_ID m_hSemMutex;
//#else
//	HANDLE m_hSemMutex;
//#endif
//};
//#endif