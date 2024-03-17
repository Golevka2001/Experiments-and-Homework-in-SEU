#ifndef _IDL_DATAREADER_H_INCLUDED_
#define _IDL_DATAREADER_H_INCLUDED_

#include "ReturnCode.h"
#include "BasicTypes.h"
#include "IDL_UserDataType.h"
#include "DDS/DomainParticipantFactory.h"
#include "DDS/Topic.h"
#include "DDS/Subscriber.h"
#include "DDS/DataReader.h"
#include "DDS/Listener/DataReaderListener.h"

class DataReaderImpl;

class GradeDataReader : public DataReader 
{
public:
	GradeDataReader(DataReaderImpl* pDataReaderImpl);

	~GradeDataReader();

	static GradeDataReader* narrow(DataReader* pDataReader);

	/* JDXCZ 
	����DataReader�е����������ϼ��Լ���Ӧ��SampleInfo�ṹ�ϼ�*/
	ReturnCode_t take(GradeSeq& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t read(GradeSeq& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);


	ReturnCode_t take_next_sample(Grade& receivedData, SampleInfo & sample_info);

};

class AverageGradeDataReader : public DataReader 
{
public:
	AverageGradeDataReader(DataReaderImpl* pDataReaderImpl);

	~AverageGradeDataReader();

	static AverageGradeDataReader* narrow(DataReader* pDataReader);

	/* JDXCZ 
	����DataReader�е����������ϼ��Լ���Ӧ��SampleInfo�ṹ�ϼ�*/
	ReturnCode_t take(AverageGradeSeq& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);

	ReturnCode_t read(AverageGradeSeq& data_values, SampleInfoSeq sample_infos, int max_samples, SampleStateKind sample_states, ViewStateKind view_states, InstanceStateKind instance_states);


	ReturnCode_t take_next_sample(AverageGrade& receivedData, SampleInfo & sample_info);

};

#endif
