#include "stdafx.h"
#include <sstream>

using namespace std;

NS_CH_BEG

TableParse::TableParse(ISqlDatabase *pSql):
	m_pSql(pSql)
{

}

TableParse::~TableParse()
{

}

string TableParse::CreateTableSqlString( Database::Type eDataBaseType, TableCreator *pTBCreator )
{
	switch(eDataBaseType)
	{
	case Database::DATABASE_MYSQL:
		DBASSERT(false);
		return "";
		break;
	case Database::DATABASE_POSTGRE:
		return CreateTableSqlPostgreString(pTBCreator);
		break;
	default:
		DBTRACE_ERROR(m_pSql,"unknown database type");
		return "";
		break;
	}
}

string TableParse::CreateTableSqlPostgreString( TableCreator *pTBCreator )
{
	ostringstream out;
	out<<"CREATE TABLE"<<pTBCreator->GetTableName()<<endl;
	out<<"(";
	for(int i=0; i<pTBCreator->GetFieldCount(); ++i)
	{
		TableField &field = pTBCreator->GetField(i);
		switch(field.GetFieldType())
		{
		case DataField::UNKNOW:
			break;
		default:
			CH_ERROR("[db] unhandled enum in TableParse::CreateTableSqlPostgreString");
			break;
		}
	}

	out<<");"<<endl;

	return out.str();
}

NS_CH_END