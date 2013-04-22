#include "stdafx.h"

NS_CH_BEG
	
PgRecordSet::PgRecordSet(PgSqlDatabase *pSqlDatabase, PGresult *pgResult,int nRowCount, int nFieldCount):
	m_pSqlDatabase(pSqlDatabase),
	m_pgResult(pgResult),
	m_records(nRowCount)
{
	m_nRowCount = nRowCount;
	m_nFieldCount = nFieldCount;

	m_records.reserve(m_nRowCount);

	for(int i=0; i<m_nRowCount; ++i)
	{
		m_records.push_back(PgRecord(this,i));
	}

}

PgRecordSet::~PgRecordSet()
{
	if(m_pgResult)
	{
		PQclear(m_pgResult);
		m_pgResult=0;
	}
	m_pSqlDatabase = 0;
}

IRecord * PgRecordSet::GetRow( int index )
{
	return (*this)[index];
}


const char * PgRecordSet::GetFieldName( uint32_t columnIndex ) const
{
	return PQfname(m_pgResult,columnIndex);
}

int PgRecordSet::GetFieldIndex( const char *szColumnName )
{
	return PQfnumber(m_pgResult,szColumnName);
}

IRecord * PgRecordSet::operator[]( uint32_t index )
{
	if(index<0)
	{
		DBTRACE_ERROR(m_pSqlDatabase,"error index less than zero index:%d",index);
		return 0;
	}

	if(index>=m_records.size())
	{
		DBTRACE_ERROR(m_pSqlDatabase," index out of range index:%d",index);
		return 0;
	}
	return &m_records[index];
}




NS_CH_END
