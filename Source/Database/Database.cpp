#include "stdafx.h"

NS_CH_BEG

class DefaultDatabaseManager : public IDatabaseManager 
{
public:
	DefaultDatabaseManager();
	virtual ~DefaultDatabaseManager();
public:
	ISqlDatabase *CreateSqlDatabase(int eDataBaseType,char **szErrorOut);

protected:
	char *m_szErrorBuffer;
};

DefaultDatabaseManager::DefaultDatabaseManager():m_szErrorBuffer(0)
{
	if(m_instance)
	{
		delete m_instance;
		m_instance=0;
	}

	m_instance = this;

	const int nBufSize = 1024;
	m_szErrorBuffer = new char[nBufSize];
	memset(m_szErrorBuffer,0,nBufSize);
}

DefaultDatabaseManager::~DefaultDatabaseManager()
{
	if(m_szErrorBuffer!=0)
	{
		delete [] m_szErrorBuffer;
		m_szErrorBuffer = 0;
	}
}

ISqlDatabase * DefaultDatabaseManager::CreateSqlDatabase( int eDataBaseType,char **szErrorOut )
{
	switch(eDataBaseType)
	{
	case Database::DATABASE_POSTGRE:
		return new PgSqlDatabase();
		break;
	case Database::DATABASE_MYSQL:
		DBASSERT(false);
		break;
	default:
		sprintf(m_szErrorBuffer,"unknow data base type, you should use DATABASE_POSTGRE or DATABASE_MYSQL or DATABASE_SQLSERVER.");
		return 0;
	}
	return 0;
}

IDatabaseManager * IDatabaseManager::m_instance;


IDatabaseManager * IDatabaseManager::GetInstancePtr()
{
	if(!m_instance)
	{
		m_instance = new DefaultDatabaseManager();
	}
	return m_instance;
}

NS_CH_END