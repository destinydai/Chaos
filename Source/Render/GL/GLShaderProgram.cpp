#include "stdafx.h"
#include <sstream>

using std::ostringstream;

NS_CH_BEG

GLShaderProgram::GLShaderProgram(IRenderDevice *pDevice):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1),
	m_nProgramID(0),
	m_ppShaderVariable(nullptr),
	m_ppShaderVertexAttribute(nullptr),
	m_nAttributeCount(-1),
	m_nUniformCount(-1)
{

}

GLShaderProgram::~GLShaderProgram()
{
	ReleaseMember();
}

bool GLShaderProgram::Compile(GLVertexShader *pVShader,GLPixelShader *pPShader)
{
	ReleaseMember();

	m_nProgramID = glCreateProgram();
	CH_GLFAILCHECK;

	char buffer[CH_BUFSIZE];
	memset(buffer, 0, CH_BUFSIZE);

	GLsizei length = 0;
	GLint status;

	glAttachShader(m_nProgramID,pVShader->GetShaderID());

	glAttachShader(m_nProgramID,pPShader->GetShaderID());

	glLinkProgram(m_nProgramID);

	// Check the link status
	glGetProgramiv ( m_nProgramID, GL_LINK_STATUS, &status );

	if(!status)
	{
		glGetProgramInfoLog(m_nProgramID, CH_BUFSIZE, &length, buffer); 
		if (length > 0) 
		{
			CH_RENDER_TRACE_ERROR(GetDevice(),"Program shader  link error:%s ",buffer);
			return false;
		}
	}

	glValidateProgram(m_nProgramID); 
	glGetProgramiv(m_nProgramID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(), "Error validating shader false" );
		return false;
	}

	glDetachShader(m_nProgramID,pVShader->GetShaderID());
	glDetachShader(m_nProgramID,pPShader->GetShaderID());

	//if no error happen
	if(!ObtainShaderProperty())
	{
		return false;
	}

	return true;
}

void GLShaderProgram::SetDepthStencilState( IDepthStencilState *pState )
{
	CH_ASSERT(false);
}

void GLShaderProgram::SetBlendState( IBlendState *pState )
{
	CH_ASSERT(false);
}

void GLShaderProgram::SetRasterizerState( IRasterizerState *pState )
{
	CH_ASSERT(false);
}

IDepthStencilState* GLShaderProgram::GetDepthStencilState()
{
	CH_ASSERT(false);
	return 0;
}

IBlendState* GLShaderProgram::GetBlendState()
{
	CH_ASSERT(false);
	return 0;
}

IRasterizerState* GLShaderProgram::GetRasterizerState()
{
	CH_ASSERT(false);
	return 0;
}

bool GLShaderProgram::ObtainShaderProperty()
{
	glGetProgramiv(m_nProgramID,GL_ACTIVE_ATTRIBUTES,&m_nAttributeCount);
	if(m_nAttributeCount<0)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: the bind shader has no vertex attribute.");
		return false;
	}
	//++m_nAttributeCount;

	GLRenderDevice *pRender = (GLRenderDevice*)GetDevice();
	char szNameBuffer[CH_BUFSIZE];

	//get vertex attribute info
	m_ppShaderVertexAttribute = new GLShaderVertexAttribute*[m_nAttributeCount];
	memset(m_ppShaderVertexAttribute,0,sizeof(GLShaderVertexAttribute*)*m_nAttributeCount);
	for(int i=0; i<m_nAttributeCount; ++i)
	{
		GLint nArraySize;
		GLenum eType;
		GLint nLocation = i;
		RVariableType::Type rVarType;
		glGetActiveAttrib(m_nProgramID,(GLuint)i,CH_BUFSIZE,nullptr,&nArraySize,&eType,szNameBuffer);

		rVarType = MapGLValueTypeToChValueType(eType);

		m_ppShaderVertexAttribute[i] = new GLShaderVertexAttribute(rVarType,szNameBuffer,i);
	}

	//get Uniforms info
	glGetProgramiv(m_nProgramID,GL_ACTIVE_UNIFORMS,&m_nUniformCount);
	if(m_nUniformCount > 0)
	{
		m_ppShaderVariable = new GLShaderVariable*[m_nUniformCount];
		memset(m_ppShaderVariable,0,sizeof(GLShaderVariable*)*m_nUniformCount);
		for(int i=0; i<m_nUniformCount; ++i)
		{
			GLint nArraySize;
			GLenum eType;
			GLint nLocation = i;
			RVariableType::Type rVarType;
			glGetActiveUniform(m_nProgramID,(GLuint)i,CH_BUFSIZE,nullptr,&nArraySize,&eType,szNameBuffer);

			rVarType = MapGLValueTypeToChValueType(eType);

			m_ppShaderVariable[i] = new GLShaderVariable(GetDevice(),this,nLocation,rVarType,szNameBuffer,nArraySize);
		}
	}
	return true;
}

void GLShaderProgram::ReleaseMember()
{
	if(m_ppShaderVariable)
	{
		int nUniforms = GetActiveUniformsCount();
		for(int i=0;i<nUniforms; ++i)
		{
			CH_SFDEL(m_ppShaderVariable[i]);
		}
		CH_SFDELARR(m_ppShaderVariable);
	}

	if(m_ppShaderVertexAttribute)
	{
		int nAttributes = GetActiveAttributeCount();
		for(int i=0; i<nAttributes; ++i)
		{
			CH_SFDEL(m_ppShaderVertexAttribute[i]);
		}
		CH_SFDELARR(m_ppShaderVertexAttribute);
	}

	if(m_nProgramID)
	{
		glDeleteProgram(m_nProgramID);
		m_nProgramID=0;
	}
}

IShaderVariable * GLShaderProgram::GetVariableByName( const char *szVariableName )
{
	int nUniforms = GetActiveUniformsCount();
	for(int i=0; i<nUniforms; ++i)
	{
		if(strcmp(m_ppShaderVariable[i]->GetVariableName(),szVariableName) == 0)
		{
			return m_ppShaderVariable[i];
		}
	}
	return nullptr;
}

IShaderVariable * GLShaderProgram::GetVariableByIndex( uint index )
{
	int nUniforms = GetActiveUniformsCount();
	if(index >= (uint)nUniforms)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"the input index is out of range. index:%d the variable count is %d",index,nUniforms);
		return nullptr;
	}
	return m_ppShaderVariable[index];
}


uint GLShaderProgram::GetVariableCount() const
{
	return m_nUniformCount;
}

string GLShaderProgram::GetActiveUniformInfos() 
{
	ostringstream out;
	out<<"Shader Variables:\n";
	for(int i=0; i<GetActiveUniformsCount(); ++i)
	{
		GLShaderVariable *pVariable = GetGLShaderVariableByIndex(i);

		out<< GetVariableTypeString(pVariable->GetVariableType()) <<"\t\t"
			<<pVariable->GetVariableName()<<"\t\t"<<pVariable->GetVariableCount()<<std::endl;
	}
	return out.str();
}

string GLShaderProgram::GetActiveAttributeInfos() 
{
	ostringstream out;
	out<<"Shader Vertex Attribute:\n";
	for(int i=0; i<GetActiveAttributeCount(); ++i)
	{
		GLShaderVertexAttribute *pAttribute = m_ppShaderVertexAttribute[i];
		
		out<<pAttribute->GetIndex()<<"\t"<<GetVariableTypeString(pAttribute->GetType())<<"\t\t"
			<<pAttribute->GetName()<<"\t\t"<<std::endl;
	}
	return out.str();
}

IShaderVertexAttribute * GLShaderProgram::GetVertexAttributeByName( const char *szName )
{
	int nAttributes = GetActiveAttributeCount();
	for(int i=0; i<nAttributes; ++i)
	{
		if(strcmp(m_ppShaderVariable[i]->GetVariableName(),szName) == 0)
		{
			return m_ppShaderVertexAttribute[i];
		}
	}
	return nullptr;
}

IShaderVertexAttribute * GLShaderProgram::GetVertexAttributeByIndex( uint index )
{
	int nAttributes = GetActiveAttributeCount();
	if(index >= (uint)nAttributes)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"the input index is out of range. index:%d the variable count is %d",index,nAttributes);
		return nullptr;
	}
	return m_ppShaderVertexAttribute[index];
}

uint GLShaderProgram::GetVertexAttributeCount() const
{
	return GetActiveAttributeCount();
}

string GLShaderProgram::ToString() 
{
	ostringstream out;
	out<<GetActiveAttributeInfos()<<GetActiveUniformInfos();
	return out.str();
}



NS_CH_END