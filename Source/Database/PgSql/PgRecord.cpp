#include "stdafx.h"

NS_CH_BEG

PgRecord::PgRecord( void ):
	m_pRecordSet(0),
	m_nRowNumber(-1),
	m_fields(0)
{
	
}

PgRecord::PgRecord( PgRecordSet *pRecordSet,int nRowID ):
	m_pRecordSet(pRecordSet),
	m_nRowNumber(nRowID),
	m_fields(pRecordSet->GetFieldCount())
{
	
}

PgRecord::~PgRecord()
{
	m_pRecordSet =0;
	m_nRowNumber = -1;
}


IRecordField * PgRecord::operator[]( uint32_t index )
{
	if(index >= (uint32_t)this->m_pRecordSet->GetFieldCount())
	{
		DBTRACE_ERROR(m_pRecordSet->GetSqlDatabase(),"index out of range index:%d, there only have %d field.",index,m_pRecordSet->GetFieldCount());
		return 0;
	}

	if(!m_fields[index].empty())
	{
		return &m_fields[index];
	}

	Oid nType = PQftype(m_pRecordSet->GetPgResult(),index);
	char *pData = PQgetvalue(m_pRecordSet->GetPgResult(),m_nRowNumber,index);
	if(pData == 0)
	{
		DBTRACE_ERROR(m_pRecordSet->GetSqlDatabase(),"PgRecord::operator[]( uint32_t index ) call PQgetvalue failed.");
		return 0;
	}

	m_fields[index] = PgRecordField(this,nType,pData);

	return &m_fields[index];
}

IRecordField * PgRecord::operator[]( const char *szFieldName )
{
	int nColumnNumber = PQfnumber(m_pRecordSet->GetPgResult(),szFieldName);
	if(nColumnNumber==-1)
	{
		return 0;
	}
	return (*this)[nColumnNumber];
}

IRecordField * PgRecord::Field( int index ) 
{
	return (*this)[index];
}

IRecordField * PgRecord::Field( char *szname) 
{
	return (*this)[szname];
}


NS_CH_END