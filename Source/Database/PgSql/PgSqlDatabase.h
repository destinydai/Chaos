#pragma once

NS_CH_BEG

class PgSqlDatabase : public ISqlDatabase
{
public:
	PgSqlDatabase();
	virtual ~PgSqlDatabase();

public://interface
	virtual int Connect(const SqlDatabaseCreateDesc &createInfo);

	virtual int Reconnect();

	//execute a sql command when not need care about the return value
	virtual int Exec(const char *szSql);

	//use sql command to query some data to store in return record set
	//failed call would be return null
	virtual IRecordSet *QueryTable(const char *szSql);

	virtual void Release() ;

	virtual int CreateTable(TableCreator *pTbDesc);

	virtual const char * GetErrorMessage() const;

	void SetErrorInfo(const char *szInfo,...);
public:	//inner use

protected:
	void ReleaseConnection();

protected:
	PGconn *m_pgConn;
	
	char *m_szErrorInfo;
};

NS_CH_END