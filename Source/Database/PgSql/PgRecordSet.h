#pragma once

NS_CH_BEG

class PgRecordSet : public IRecordSet
{
public:
	PgRecordSet(PgSqlDatabase *pSqlDatabase, PGresult *pgResult,int nRowCount, int nFieldCount);
	virtual ~PgRecordSet();

public://interface
	virtual IRecord *operator[](uint32_t index);

	virtual IRecord *GetRow(int index);

	virtual const char *GetFieldName(uint32_t columnIndex) const;

	virtual int GetFieldIndex(const char *szColumnName);

	virtual void Release() { delete this; }
public: // inner use
	inline PgSqlDatabase *GetSqlDatabase() { return m_pSqlDatabase; }
	PGresult *GetPgResult() { return m_pgResult; }
protected:
	PGresult *m_pgResult;
	PgSqlDatabase *m_pSqlDatabase;
	vector<PgRecord> m_records;
	
};

NS_CH_END