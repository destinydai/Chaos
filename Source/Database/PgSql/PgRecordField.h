#pragma once

NS_CH_BEG

class PgRecordField : public IRecordField
{
public:
	PgRecordField();
	PgRecordField(PgRecord *pRecord,Oid nDataType,const char *pData);
	virtual ~PgRecordField();

public://interface

	bool	    ToBoolean() const;
	int8_t   ToInt8() const;
	int16_t ToInt16() const;
	int32_t ToInt32() const;
	int64_t ToInt64() const;
	float		 ToFloat() const;
	double ToDouble() const;
	string   ToString() const;
	
	int GetDataSize() const;
	void GetData(char *pBuffer, int nBufSize);

public://inter use
	bool empty() const { return m_pData == 0; }
protected:
	PgRecord *m_pRecord;
	const char *m_pData;
};

NS_CH_END