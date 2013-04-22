#include "stdafx.h"


NS_CH_BEG

TableField::TableField( ISqlDatabase *pSql, DataField::Type eType,const char *szName ):
	m_pSql(pSql),
	m_bRefKey(false),
	m_bPrimaryKey(false),
	m_eDataType(eType),
	m_szName(szName),
	m_nAutoIncrease(0),
	m_nStringLength(DEFAULT_STRING_LENGTH)
{
	memset(m_szStringValue,0,DEFAULT_STRING_LENGTH);
}

TableField::~TableField()
{

}

TableField & TableField::SetPrimary()
{
	m_bPrimaryKey = true;
	return *this;
}

inline bool IsInteger(DataField::Type eType)
{
	if(eType == DataField::CHAR || eType == DataField::INT16 || 
		eType == DataField::INT32 || eType == DataField::INT64)
	{
		return true;
	}
	return false;
}

TableField & TableField::SetAutoIncrease( int nIncreaseSetp )
{
	if(!IsInteger(GetFieldType()))
	{
		DBTRACE_ERROR(m_pSql,"auto increase attribute must set on type integer.");
		return *this;
	}
	m_nAutoIncrease = nIncreaseSetp;
	return *this;
}

TableField & TableField::SetDefaultValue( int8_t value )
{
	if(!IsInteger(GetFieldType()))
	{
		DBTRACE_ERROR(m_pSql,"this field is not a integer");
		return *this;
	}
	m_int8Value = value;
	return *this;
}

TableField & TableField::SetDefaultValue( int16_t value )
{
	if(!IsInteger(GetFieldType()))
	{
		DBTRACE_ERROR(m_pSql,"this field is not a integer");
		return *this;
	}
	m_int16Value = value;
	return *this;
}

TableField & TableField::SetDefaultValue( int32_t value )
{
	if(!IsInteger(GetFieldType()))
	{
		DBTRACE_ERROR(m_pSql,"this field is not a integer");
		return *this;
	}
	m_int32Value = value;
	return *this;
}

TableField & TableField::SetDefaultValue( int64_t value )
{
	if(!IsInteger(GetFieldType()))
	{
		DBTRACE_ERROR(m_pSql,"this field is not a integer");
		return *this;
	}
	m_int64Value = value;
	return *this;
}

TableField & TableField::SetDefaultValue( float value )
{
	if(GetFieldType() != DataField::FLOAT && GetFieldType() != DataField::DOUBLE)
	{
		DBTRACE_ERROR(m_pSql,"this field is not a float value");
		return *this;
	}
	m_floatValue = value;
	return *this;
}

TableField & TableField::SetDefaultValue( double value )
{
	if(GetFieldType() != DataField::FLOAT && GetFieldType() != DataField::DOUBLE)
	{
		DBTRACE_ERROR(m_pSql,"this field is not a float value");
		return *this;
	}
	m_doubleValue = value;
	return *this;
}

TableField & TableField::SetDefaultValue( const char *szString )
{
	if(GetFieldType() != DataField::STRING)
	{
		DBTRACE_ERROR(m_pSql,"this field is not a string");
		return *this;
	}

	if(strlen(szString)>DEFAULT_STRING_LENGTH - 1)
	{
		DBTRACE_ERROR(m_pSql,"if set a string default value, the default string length must less than %d",DEFAULT_STRING_LENGTH);
		return *this;
	}
	strcpy(m_szStringValue,szString);
	return *this;
}

TableField & TableField::SetReferenceKey( const char *szRefTb,const char *szRefField )
{
	m_szRefKeyTbName = szRefTb;
	m_szRefKeyFieldName = szRefField;

	m_bRefKey = true;
	return *this;
}

NS_CH_END