#pragma once


NS_CH_BEG

class TableParse
{
public:
	TableParse(ISqlDatabase *pSql);
	~TableParse();

public:
	string CreateTableSqlString(Database::Type eDataBaseType, TableCreator *pTBCreator);
private:
	string CreateTableSqlPostgreString(TableCreator *pTBCreator);

private:
	ISqlDatabase *m_pSql;
};

NS_CH_END