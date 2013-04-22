#include "stdafx.h"

NS_CH_BEG

GLShaderVariable::GLShaderVariable( IRenderDevice *pDevice,GLShaderProgram *pProgram,GLint nUniformLocation,
	RVariableType::Type eVarType,const char *szName,uint nArraySize ):
	m_pRenderDevice(pDevice),m_pShaderProgram(pProgram),m_nUnifornLocation(nUniformLocation),
	m_szVarName(nullptr),m_nArraySize(nArraySize),m_varType(eVarType)
{
	CH_ASSERT(szName);
	uint nLen = strlen(szName);
	m_szVarName = new char[nLen+1];
	strcpy(m_szVarName,szName);

}

GLShaderVariable::~GLShaderVariable( void )
{
	CH_SFDELARR(m_szVarName);
}

RVariableType::Type GLShaderVariable::GetVariableType() const
{
	return m_varType;
}

const char * GLShaderVariable::GetVariableName() const
{
	return m_szVarName;
}

uint GLShaderVariable::GetVariableCount() const
{
	return m_nArraySize;
}

void GLShaderVariable::SetFloat( const float *pValue,uint nCount )
{
	if(nCount==1)
		glUniform1f(m_nUnifornLocation,*pValue);
	else
		glUniform1fv(m_nUnifornLocation,nCount,pValue);
}

void GLShaderVariable::SetInt( const int32 *pValue,uint nCount )
{
	if(nCount==1)
		glUniform1i(m_nUnifornLocation,*pValue);
	else
		glUniform1iv(m_nUnifornLocation,nCount,pValue);
}

void GLShaderVariable::SetBool( const boolean *pValue,uint nCount )
{
	if(nCount==1)
		glUniform1i(m_nUnifornLocation,*pValue);
	else
		glUniform1iv(m_nUnifornLocation,nCount,pValue);
}

void GLShaderVariable::SetVector2( const Vector2 *pVectors,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::VEC2);
	if(nCount==1)
		glUniform2f(m_nUnifornLocation,pVectors->x,pVectors->y);
	else
		glUniform2fv(m_nUnifornLocation,nCount,(const GLfloat*)pVectors);
}

void GLShaderVariable::SetVector3( const Vector3 *pVectors,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::VEC3);
	if(nCount==1)
		glUniform3f(m_nUnifornLocation,pVectors->x,pVectors->y,pVectors->z);
	else
		glUniform3fv(m_nUnifornLocation,nCount,(const GLfloat*)pVectors);
}

void GLShaderVariable::SetVector4( const Vector4 *pVectors,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::VEC4);
	if(nCount==1)
		glUniform4f(m_nUnifornLocation,pVectors->x,pVectors->y,pVectors->z,pVectors->z);
	else
		glUniform4fv(m_nUnifornLocation,nCount,(const GLfloat*)pVectors);
}

void GLShaderVariable::SetInt2( const int *pIntegers,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::INT2);
	if(nCount==1)
		glUniform2i(m_nUnifornLocation,pIntegers[0],pIntegers[1]);
	else
		glUniform2iv(m_nUnifornLocation,nCount,pIntegers);
}

void GLShaderVariable::SetInt3( const int *pIntegers,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::INT3);
	if(nCount==1)
		glUniform3i(m_nUnifornLocation,pIntegers[0],pIntegers[1],pIntegers[2]);
	else
		glUniform3iv(m_nUnifornLocation,nCount,pIntegers);
}

void GLShaderVariable::SetInt4( const int *pIntegers,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::INT4);
	if(nCount==1)
		glUniform4i(m_nUnifornLocation,pIntegers[0],pIntegers[1],pIntegers[2],pIntegers[3]);
	else
		glUniform4iv(m_nUnifornLocation,nCount,pIntegers);
}

void GLShaderVariable::SetMatrix2( const Matrix2 *pMatrixes,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::MAT2);
	glUniformMatrix2fv(m_nUnifornLocation,nCount,false,(const GLfloat*)&pMatrixes[0]);
}

void GLShaderVariable::SetMatrix3( const Matrix3 *pMatrixes,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::MAT3);
	glUniformMatrix3fv(m_nUnifornLocation,nCount,false,(const GLfloat*)&pMatrixes[0]);
}

void GLShaderVariable::SetMatrix4( const Matrix4 *pMatrixes,uint nCount )
{
	CH_ASSERT(m_varType == RVariableType::MAT4);
	glUniformMatrix4fv(m_nUnifornLocation,nCount,false,(const GLfloat*)&pMatrixes[0]);
}

void GLShaderVariable::SetTexture2D( uint slot,ITexture2D *pTexture )
{
	CH_ASSERT(m_varType == RVariableType::SAMPLER_2D);
	if(slot>7)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"GLES only support 8 texture unit. current input parm slot is %d",slot);
		return;
	}
	GLenum eTexture = GL_TEXTURE0 + slot;
	glActiveTexture(eTexture);
	glBindTexture(GL_TEXTURE_2D,((GLTexture2D*)pTexture)->GetID());
	glUniform1i(m_nUnifornLocation,slot);
	
	CH_GLFAILCHECK;
}


NS_CH_END