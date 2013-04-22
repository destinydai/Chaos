#include "stdafx.h"

//包含一下文件定义的数据类型，出现编译错误，
//以下直接映射关心的类型
//#include "catalog/pg_type.h"
#define BOOLOID			16
#define CHAROID			18
#define BYTEAOID		17
#define INT2OID			21
#define INT4OID			23
#define INT8OID			20
#define TEXTOID			25
#define FLOAT4OID 700
#define FLOAT8OID 701
#define TIMESTAMPOID	1114	//date and time
#define VARBITOID	  1562			//Binary

#define DB_TYPE_CHECK(tagType) \
	if(m_eDataType!=tagType)\
	{\
		DBTRACE_ERROR(m_pRecord->GetRecordSet()->GetSqlDatabase(),"can not convert %d type to %d type.",tagType,m_eDataType);\
		DBASSERT(m_eDataType==tagType);\
	}


NS_CH_BEG

PgRecordField::PgRecordField():
	m_pRecord(0),
	m_pData(0)
{
	m_eDataType = DataField::UNKNOW;
}

PgRecordField::PgRecordField( PgRecord *pRecord,Oid nDataType,const char *pData ):
	m_pRecord(pRecord),
	m_pData(pData)
{
	switch(nDataType)
	{
	case BOOLOID:
		m_eDataType = DataField::BOOLEAN;
		break;
	case CHAROID:
		m_eDataType = DataField::CHAR;
		break;
	case BYTEAOID:
		m_eDataType = DataField::STRING;
		break;
	case INT2OID:
		m_eDataType = DataField::INT16;
		break;
	case INT4OID:
		m_eDataType = DataField::INT32;
		break;
	case INT8OID:
		m_eDataType = DataField::INT64;
		break;
	case TEXTOID:
		m_eDataType = DataField::TEXT;
		break;
	case FLOAT4OID:
		m_eDataType = DataField::FLOAT;
		break;
	case FLOAT8OID:
		m_eDataType = DataField::DOUBLE;
		break;
	case TIMESTAMPOID:
		m_eDataType = DataField::DATETIME;
		break;
	case VARBITOID:
		m_eDataType = DataField::BINARY;
		break;
	default:
		DBTRACE_ERROR(m_pRecord->GetRecordSet()->GetSqlDatabase(),"PgRecordField unprocessed data type");
		DBASSERT(false);
		break;
	}


}

PgRecordField::~PgRecordField()
{

}

bool PgRecordField::ToBoolean() const
{
	DB_TYPE_CHECK(DataField::BOOLEAN);
	return *((bool*)m_pData);
}

int8_t PgRecordField::ToInt8() const
{
	DB_TYPE_CHECK(DataField::CHAR);
	return *((int8_t*)m_pData);
}

int16_t PgRecordField::ToInt16() const
{
	DB_TYPE_CHECK(DataField::INT16);
	return *((int16_t*)m_pData);
}

int32_t PgRecordField::ToInt32() const
{
	DB_TYPE_CHECK(DataField::INT32);
	return *((int32_t*)m_pData);
}

int64_t PgRecordField::ToInt64() const
{
	DB_TYPE_CHECK(DataField::INT64);
	return *((int64_t*)m_pData);
}

float PgRecordField::ToFloat() const
{
	DB_TYPE_CHECK(DataField::FLOAT);
	return *((float*)m_pData);
}

double PgRecordField::ToDouble() const
{
	DB_TYPE_CHECK(DataField::DOUBLE);
	return *((double*)m_pData);
}

string PgRecordField::ToString() const
{
	DB_TYPE_CHECK(DataField::STRING);
	return string(m_pData);
}

int PgRecordField::GetDataSize() const
{
	DBASSERT(false);
	return -1;
}

void PgRecordField::GetData( char *pBuffer, int nBufSize )
{
	if(pBuffer==0)
	{
		DBTRACE_ERROR(m_pRecord->GetRecordSet()->GetSqlDatabase(),"the input parm pBuffer equal null");
		return;
	}
	
	DBASSERT(false);
}

NS_CH_END


#undef DB_TYPE_CHECK