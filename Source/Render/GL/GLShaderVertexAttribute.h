#pragma once


NS_CH_BEG


class GLShaderVertexAttribute : public IShaderVertexAttribute
{
public:
	GLShaderVertexAttribute(RVariableType::Type eType,const char *szName,int index);
	  ~GLShaderVertexAttribute();
public: //interface 
	const char *GetName() const;
	uint GetIndex() const;
	RVariableType::Type GetType() const ;
private:
	RVariableType::Type m_varType;
	char *m_szName;
	int m_nIndex;
};


NS_CH_END