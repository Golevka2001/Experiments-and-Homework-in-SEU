#include "IDL_DataWriter.h"

GradeDataWriter::GradeDataWriter(DataWriterImpl * pDataWriterImpl)
	: DataWriter(pDataWriterImpl)
{
}

GradeDataWriter::~GradeDataWriter()
{
}

GradeDataWriter* GradeDataWriter::narrow(DataWriter* pDataWriter) 
{
	if (!pDataWriter)
		return NULL;
	GradeDataWriter *aGradeDataWriter = (GradeDataWriter*)pDataWriter;
    return aGradeDataWriter;
}

ReturnCode_t GradeDataWriter::write(Grade& data, const InstanceHandle_t & handle){
	char *buf = new char[DEFAULT_CDRSIZE];
	CDR* CDRData = NULL;
	ReturnCode_t ret = RETCODE_OK;
	CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
	data.Marshal(CDRData);
	char* myData = CDRData->GetBufferPtr();
	int typeSize = CDRData->GetContentLen();
	char* pDataVale = new char[typeSize + 4]();
	pDataVale[1] = 0x01;
	memcpy(pDataVale + 4, myData, typeSize);
	//InstanceHandle_t handle = HANDLE_NIL;
	ret = DataWriter::write(pDataVale, typeSize + 4, handle);
	buf = (char*)CDRData->pReal_buffer;
	if (buf)
		delete buf;
	if (CDRData)
		delete CDRData;
	if (pDataVale)
		delete pDataVale;
	return ret;
}

AverageGradeDataWriter::AverageGradeDataWriter(DataWriterImpl * pDataWriterImpl)
	: DataWriter(pDataWriterImpl)
{
}

AverageGradeDataWriter::~AverageGradeDataWriter()
{
}

AverageGradeDataWriter* AverageGradeDataWriter::narrow(DataWriter* pDataWriter) 
{
	if (!pDataWriter)
		return NULL;
	AverageGradeDataWriter *aAverageGradeDataWriter = (AverageGradeDataWriter*)pDataWriter;
    return aAverageGradeDataWriter;
}

ReturnCode_t AverageGradeDataWriter::write(AverageGrade& data, const InstanceHandle_t & handle){
	char *buf = new char[DEFAULT_CDRSIZE];
	CDR* CDRData = NULL;
	ReturnCode_t ret = RETCODE_OK;
	CDRData = new CDR((unsigned char *)buf, DEFAULT_CDRSIZE, MY_BYTE_SEX, 1);
	data.Marshal(CDRData);
	char* myData = CDRData->GetBufferPtr();
	int typeSize = CDRData->GetContentLen();
	char* pDataVale = new char[typeSize + 4]();
	pDataVale[1] = 0x01;
	memcpy(pDataVale + 4, myData, typeSize);
	//InstanceHandle_t handle = HANDLE_NIL;
	ret = DataWriter::write(pDataVale, typeSize + 4, handle);
	buf = (char*)CDRData->pReal_buffer;
	if (buf)
		delete buf;
	if (CDRData)
		delete CDRData;
	if (pDataVale)
		delete pDataVale;
	return ret;
}

