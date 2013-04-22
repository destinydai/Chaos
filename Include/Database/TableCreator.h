#pragma once


NS_CH_BEG

class TableCreator
{
public:
	TableCreator(ISqlDatabase *pSql,const char *szTableName);
	TableCreator(ISqlDatabase *pSql,const char *szTableName,IRecordSet *pRSet);
	virtual ~TableCreator();
public:
	const char *GetTableName() const { return m_szTBName.c_str(); }
	TableField &AddField(DataField::Type eFieldType, const char *szFieldName);
	void RemoveField(const char *szFieldName);
	int GetFieldCount() const { return (int)m_fields.size(); }
	TableField &GetField(uint32_t nIndex)  { DBASSERT(nIndex<m_fields.size());  return *m_fields[nIndex]; }

	void Clear();

	ISqlDatabase* GetSqlConnection() { return m_pSql;}
protected:
	vector<TableField*> m_fields;
	ISqlDatabase *m_pSql;
	string m_szTBName;
};


NS_CH_END