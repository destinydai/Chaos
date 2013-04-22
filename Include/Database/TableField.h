#pragma once



NS_CH_BEG

class TableField
{
public:
	enum
	{
		DEFAULT_STRING_LENGTH = 256
	};

protected:
	TableField(ISqlDatabase *pSql, DataField::Type eType,const char *szName);
	virtual ~TableField();

	TableField(const TableField &o);
public:
	TableField &SetPrimary();
	TableField &SetAutoIncrease(int nIncreaseSetp);

	TableField &SetDefaultValue(int8_t value);
	TableField &SetDefaultValue(int16_t value);
	TableField &SetDefaultValue(int32_t value);
	TableField &SetDefaultValue(int64_t value);
	TableField &SetDefaultValue(float value);
	TableField &SetDefaultValue(double value);
	TableField &SetDefaultValue(const char *szString);
	TableField &SetReferenceKey(const char *szRefTb,const char *szRefField);
	
	const char *GetFieldName() const { return m_szName.c_str(); }
	DataField::Type GetFieldType() const { return m_eDataType; }

	bool IsPrimaryKey() const { return m_bPrimaryKey; }

	bool IsRefereneKey() const { return m_bRefKey; }
	const char *GetRefTableName() const { return m_szRefKeyTbName.c_str(); }
	const char *GetRefFieldName() const { return m_szRefKeyFieldName.c_str(); }

	int GetAutoIncrease() const { return m_nAutoIncrease;  }

	uint32_t GetVarcharLength() const { return m_nStringLength; }
protected:
	string m_szName;
	DataField::Type m_eDataType;
	bool m_bPrimaryKey;

	bool m_bRefKey;
	string m_szRefKeyTbName;
	string m_szRefKeyFieldName;

	int m_nAutoIncrease;
	//the varchar thus string max length. 
	int m_nStringLength;

	ISqlDatabase *m_pSql;

	union
	{
		int8_t m_int8Value;
		int16_t m_int16Value;
		int32_t m_int32Value;
		int64_t m_int64Value;
		float  m_floatValue;
		double m_doubleValue;
		char m_szStringValue[DEFAULT_STRING_LENGTH];
	};

	friend class TableCreator;
};


NS_CH_END