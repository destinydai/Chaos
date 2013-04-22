#pragma once


#define DBASSERT(x) CH_ASSERT(x)
#define DBTRACE(...) CH_TRACE(__VA_ARGS__)


NS_CH_BEG

namespace Database
{
	enum Type
	{
		DATABASE_UNKNOW=0,
		DATABASE_POSTGRE=1,
		DATABASE_MYSQL=2
	};
}


namespace ErrorCode
{
	enum Type
	{
		ERROR_OK=0,
		INVALID_ENUM,
		INVALID_PARM,
		INVALID_CALL,
		EXECUTE_FAILED,
		INDEX_OUT_RANGE
	};
}

namespace DataField
{
	enum Type
	{
		UNKNOW=0,
		BOOLEAN,
		CHAR,
		STRING,
		INT16,
		INT32,
		INT64,
		TEXT,
		FLOAT,
		DOUBLE,
		DATETIME,
		BINARY
	};
}


struct SqlDatabaseCreateDesc
{
	char szHostName[128];
	char szHostAddr[128];
	uint32_t nHostPort;
	char szDBName[128];
	char szUser[128];
	char szPassword[128];
	uint32_t nConnectTimeOut;					//unit is second, 0 means wait until connect finished
	char szClientEncoding[128];				//
	uint32_t bKeeplives;

	SqlDatabaseCreateDesc()
	{
		memset(this,0,sizeof(SqlDatabaseCreateDesc));
		bKeeplives = true;
	}

};


class IRecordField;
class IRecord;
class IRecordSet;
class ISqlDatabase;

class TableField;
class TableCreator;

class IRecordField
{
public:
	const char *GetFieldName() const { return m_szFieldName; }
	DataField::Type GetFieldType() const { return m_eDataType; }

	virtual bool	 ToBoolean() const=0;
	virtual int8_t   ToInt8() const=0;
	virtual int16_t ToInt16() const=0;
	virtual int32_t ToInt32() const=0;
	virtual int64_t ToInt64() const=0;
	virtual float	 ToFloat() const=0;
	virtual double ToDouble() const=0;
	virtual string   ToString() const=0;

	virtual int GetDataSize() const=0;
	virtual void GetData(char *pBuffer, int nBufSize)=0;

protected:
	const char *m_szFieldName;
	DataField::Type m_eDataType;
};


class IRecord
{
public:
	virtual IRecordField *Field(int index)  =0;
	virtual IRecordField  *Field(char *szname)  =0;

	virtual IRecordField *operator[](uint32_t index)=0;
	virtual IRecordField *operator[](const char *szFieldName)=0;

	inline int GetFieldCount() const { return m_nFieldCount; } 

protected:
	int m_nFieldCount;
};

class IRecordSet
{
public:
	virtual IRecord *operator[](uint32_t index)=0;

	//if error occur,  return null, check belonged ISqlDatabase object to get more information
	virtual IRecord *GetRow(int index)=0;

	//Returns the column name associated with the given column number.
	//null is returned if the column number is out of range.
	virtual const char *GetFieldName(uint32_t columnIndex) const=0;

	//Returns the column index associated with the given column name.
	//-1 is returned if the given name does not match any column.
	//column index start at 0
	virtual int GetFieldIndex(const char *szColumnName)=0;

	virtual void Release() =0;

	inline int GetRowCount() const { return m_nRowCount; };

	//returns the number of columns (fields) in each row of the query result.
	inline int GetFieldCount() const { return m_nFieldCount; }

protected:
	int m_nRowCount;
	int m_nFieldCount;
};

class IRecordTable
{
	
};


class ISqlDatabase
{
public:

	virtual int Connect(const SqlDatabaseCreateDesc &createInfo)=0;

	virtual int Reconnect()=0;

	//execute a sql command when not need care about the return value
	//return 0 indicate no error happened
	virtual int Exec(const char *szSql)=0;

	//use sql command to query some data to store in return record set
	//failed call would be return null
	virtual IRecordSet *QueryTable(const char *szSql)=0;

	virtual void Release() =0;

	virtual int CreateTable(TableCreator *pTbDesc) =0;

	virtual const char * GetErrorMessage() const=0;

	virtual void SetErrorInfo(const char *szInfo,...) =0;
};


class IDatabaseManager
{
public:
	static IDatabaseManager *GetInstancePtr(); 

	//if some error occur this return pointer would be null
	// and szErrorOut will be the error info
	//don't delete szErrorOut even its not null
	virtual ISqlDatabase *CreateSqlDatabase(int eDataBaseType,char **szErrorOut)=0;

protected:
	static IDatabaseManager *m_instance;
};


NS_CH_END

#include "TableField.h"
#include "TableCreator.h"
