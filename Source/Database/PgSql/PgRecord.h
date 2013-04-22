#pragma once

NS_CH_BEG

class PgRecord : public IRecord
{
public:
	PgRecord(void);
	PgRecord(PgRecordSet *pRecordSet,int nRowID);
	virtual ~PgRecord();

	virtual IRecordField *Field(int index) ;
	virtual IRecordField  *Field(char *szname)  ;

	virtual IRecordField *operator[](uint32_t index);
	virtual IRecordField *operator[](const char *szFieldName);

public://inner use
	PgRecordSet *GetRecordSet() { return m_pRecordSet; }

protected:
	int m_nRowNumber;
	PgRecordSet *m_pRecordSet;
	vector<PgRecordField> m_fields;
};

NS_CH_END