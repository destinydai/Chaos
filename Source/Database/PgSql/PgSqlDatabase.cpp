#include "stdafx.h"


NS_CH_BEG

enum PG_CREATE_OPT
{
	PG_HOST_NAME,
	PG_HOST_ADDR,
	PG_HOST_PORT,
	PG_DB_NAME,
	PG_USER,
	PG_PASSWORD,
	PG_CONNECT_TIME_OUT,
	PG_CLIENT_ENCODING,
	PG_KEEP_LIVES,

	PG_COUNT,
};

struct PgCreateValues
{
	char szHostName[128];
	char szHostAddr[128];
	char szHostPort[64];
	char szDBName[128];
	char szUser[128];
	char szPassword[128];
	char szConnectTimeOut[32];					
	char szClientEncoding[128];				
	char szKeeplives[32];

	PgCreateValues()
	{
		memset(this,0,sizeof(PgCreateValues));
	}
};

const int m_cBufSize = 2048;

PgSqlDatabase::PgSqlDatabase():
	m_szErrorInfo(0),
	m_pgConn(0)
{
	
	m_szErrorInfo = new char[m_cBufSize];
	memset(m_szErrorInfo,0,m_cBufSize);
}

PgSqlDatabase::~PgSqlDatabase()
{
	this->ReleaseConnection();
	if(m_szErrorInfo)
	{
		delete [] m_szErrorInfo;
		m_szErrorInfo=0;
	}
}

int PgSqlDatabase::Connect( const SqlDatabaseCreateDesc &createInfo )
{
	this->ReleaseConnection();
	
	char pBuf[1024];
	char* ppKeys[PG_COUNT+1]= {0};
	char* ppValues[PG_COUNT+1]= {0};
	uint32_t nConnectTimeout = createInfo.nConnectTimeOut;

	PgCreateValues values;

	ppKeys[PG_HOST_NAME] = "host";
	ppKeys[PG_HOST_ADDR] = "hostaddr";
	ppKeys[PG_HOST_PORT] = "port";
	ppKeys[PG_DB_NAME] = "dbname";
	ppKeys[PG_USER] = "user";
	ppKeys[PG_PASSWORD] = "password";
	ppKeys[PG_CONNECT_TIME_OUT] = "connect_timeout";
	ppKeys[PG_CLIENT_ENCODING] = "client_encoding";
	ppKeys[PG_KEEP_LIVES] = "keepalives";

	ppValues[PG_HOST_NAME] = values.szHostName;
	ppValues[PG_HOST_ADDR] = values.szHostAddr;
	ppValues[PG_HOST_PORT] = values.szHostPort;
	ppValues[PG_DB_NAME] = values.szDBName;
	ppValues[PG_USER] = values.szUser;
	ppValues[PG_PASSWORD] = values.szPassword;
	ppValues[PG_CONNECT_TIME_OUT] = values.szConnectTimeOut;
	ppValues[PG_CLIENT_ENCODING] = values.szClientEncoding;
	ppValues[PG_KEEP_LIVES] = values.szKeeplives;

	//validate the createInfo
	if(strlen(createInfo.szHostName) == 0)
	{
		DBTRACE_ERROR(this,"error you must set a valid host name.");
		return ErrorCode::INVALID_PARM;
	}

	if(strlen(createInfo.szHostAddr) == 0)
	{
		DBTRACE_ERROR(this," you must set a valid host address.");
		return ErrorCode::INVALID_PARM;
	}

	if(createInfo.nHostPort >=65535)
	{
		DBTRACE_ERROR(this," error you must set a valid host port.");
		return ErrorCode::INVALID_PARM;
	}

	if(strlen(createInfo.szDBName) == 0)
	{
		DBTRACE_ERROR(this," error you must set a valid db name.");
		return ErrorCode::INVALID_PARM;
	}

	if(strlen(createInfo.szUser) == 0)
	{
		DBTRACE_ERROR(this," error you must set a valid user name.");
		return ErrorCode::INVALID_PARM;
	}

	if(strlen(createInfo.szPassword) ==0 )
	{
		DBTRACE_ERROR(this," error password should be set.");
		return ErrorCode::INVALID_PARM;
	}

	//copy create info into values
	strcpy(values.szHostName,createInfo.szHostName);
	strcpy(values.szHostAddr,createInfo.szHostAddr);
	sprintf(pBuf,"%d",createInfo.nHostPort);
	strcpy(values.szHostPort,pBuf);
	strcpy(values.szDBName,createInfo.szDBName);
	strcpy(values.szUser,createInfo.szUser);
	strcpy(values.szPassword,createInfo.szPassword);
	sprintf(pBuf,"%d",createInfo.nConnectTimeOut);
	strcpy(values.szConnectTimeOut,pBuf);
	if(strlen(createInfo.szClientEncoding)==0)
	{
		strcpy(values.szClientEncoding,"auto");
	}
	else
	{
		strcpy(values.szClientEncoding,createInfo.szClientEncoding);
	}
	if(createInfo.bKeeplives)
	{
		strcpy(values.szKeeplives,"1");
	}
	else
	{
		strcpy(values.szKeeplives,"0");
	}

	m_pgConn = PQconnectdbParams(ppKeys,ppValues,0);

	if (PQstatus(m_pgConn) != CONNECTION_OK)
	{
		DBTRACE_ERROR(this,"%s",PQerrorMessage(m_pgConn));
		return ErrorCode::EXECUTE_FAILED;
	}

	return ErrorCode::ERROR_OK;
}

int PgSqlDatabase::Reconnect()
{
	return 0;
}

int PgSqlDatabase::Exec( const char *szSql )
{
	if(0 == szSql)
	{
		DBTRACE_ERROR(this,"the szSql parameter is null.");
		return ErrorCode::INVALID_PARM;
	}

	if(!m_pgConn)
	{
		DBTRACE_ERROR(this,"please connect database first");
		return ErrorCode::INVALID_CALL;
	}

	PGresult *pgResult = PQexec(m_pgConn,szSql);

	if (PQresultStatus(pgResult) != PGRES_COMMAND_OK)
	{
		PQclear(pgResult);
		pgResult=0;
		return ErrorCode::EXECUTE_FAILED;
	}

	PQclear(pgResult);
	return ErrorCode::ERROR_OK;
}

IRecordSet * PgSqlDatabase::QueryTable( const char *szSql )
{
	if(0 == szSql)
	{
		DBTRACE_ERROR(this," szSql parameter is null.");
		return 0;
	}

	if(!m_pgConn)
	{
		DBTRACE_ERROR(this,"please connect database first");
		return 0;
	}

	PGresult *pgResult = PQexec(m_pgConn,szSql);

	if (PQresultStatus(pgResult) != PGRES_COMMAND_OK)
	{
		PQclear(pgResult);
		pgResult=0;
		return 0;
	}

	int nRowCount = PQntuples(pgResult);
	int nFieldCount = PQnfields(pgResult);

	return new PgRecordSet(this,pgResult,nRowCount,nFieldCount);
}


void PgSqlDatabase::Release()
{
	delete this;
}

void PgSqlDatabase::ReleaseConnection()
{
	if(m_pgConn)
	{
		PQfinish(m_pgConn);
		m_pgConn = 0;
	}
}

void PgSqlDatabase::SetErrorInfo(const char *szInfo,...)
{
	va_list argList;
	va_start(argList,szInfo);
	vsprintf(m_szErrorInfo,szInfo,argList);
	va_end(argList);
}

const char * PgSqlDatabase::GetErrorMessage() const
{
	return m_szErrorInfo;
}

int PgSqlDatabase::CreateTable( TableCreator *pTbDesc )
{
	if(pTbDesc==0)
	{
		DBTRACE_ERROR(this,"the input parm pTbDesc is null");
		return ErrorCode::INVALID_PARM;
	}

	if(pTbDesc->GetSqlConnection() != this)
	{
		DBTRACE_ERROR(this,"the table creator not beglone this database connection.");
		return ErrorCode::INVALID_CALL;
	}
	
	TableParse tbParse(this);
	 string szSql = tbParse.CreateTableSqlString(Database::DATABASE_POSTGRE,pTbDesc);
	 return this->Exec(szSql.c_str());
}

NS_CH_END