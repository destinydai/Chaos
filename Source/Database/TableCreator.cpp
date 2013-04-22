#include "stdafx.h"


NS_CH_BEG

TableCreator::TableCreator(ISqlDatabase *pSql,const char *szTableName ):
	m_pSql(pSql)
{

}

TableCreator::TableCreator(ISqlDatabase *pSql, const char *szTableName,IRecordSet *pRSet ):
	m_pSql(pSql)
{

}

TableCreator::~TableCreator()
{
	Clear();
}

static inline bool CheckHasItem(const char *szName,vector<TableField*> fields,uint32_t &nIndex)
{
	for(uint32_t i=0; i<fields.size(); ++i)
	{
		if(strcmp(szName,fields[i]->GetFieldName())==0)
		{
			nIndex = i;
			return true;
		}
	}
	return false;
}

TableField & TableCreator::AddField( DataField::Type eFieldType, const char *szFieldName )
{
	uint32_t nIndex=0;
	if(CheckHasItem(szFieldName,m_fields,nIndex))
	{
		DBTRACE_ERROR(m_pSql,"already has the field name:%s",szFieldName);
		return *m_fields[nIndex];
	}

	TableField *pField = new TableField(m_pSql,eFieldType,szFieldName);
	m_fields.push_back(pField);
	return *pField;
}

void TableCreator::RemoveField( const char *szFieldName )
{
	uint32_t nIndex=0;
	if(CheckHasItem(szFieldName,m_fields,nIndex))
	{
		m_fields.erase(m_fields.begin() + nIndex);
	}
}

void TableCreator::Clear()
{
	for(uint32_t i=0; i<m_fields.size(); ++i)
	{
		delete m_fields[i];
		m_fields[i]=0;
	}
	m_fields.clear();
}



NS_CH_END