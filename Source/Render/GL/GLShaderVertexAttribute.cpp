#include "stdafx.h"


NS_CH_BEG



	GLShaderVertexAttribute::GLShaderVertexAttribute( RVariableType::Type eType,const char *szName,int index ) :
m_varType(eType),m_szName(0),m_nIndex(index)
{
	int nLen = strlen(szName)+1;
	CH_ASSERT(nLen-1>0);
	m_szName = new char[nLen];
	memcpy(m_szName,szName,nLen);
}

GLShaderVertexAttribute::~GLShaderVertexAttribute()
{
	CH_SFDELARR(m_szName);
}

RVariableType::Type GLShaderVertexAttribute::GetType() const
{
	return m_varType;
}

const char * GLShaderVertexAttribute::GetName() const
{
	return m_szName;
}

uint GLShaderVertexAttribute::GetIndex() const
{
	return m_nIndex;
}

NS_CH_END