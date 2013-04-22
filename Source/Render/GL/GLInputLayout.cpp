#include "stdafx.h"


NS_CH_BEG

GLInputLayout::GLInputLayout(IRenderDevice *pDevice ):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1),
	m_pLayouts(nullptr),
	m_nLayoutCount(0),
	m_nVertexSize(0)
{
	memset(m_pEleCount,0,sizeof(uint)*GLRenderDevice::INPUT_VERTEX_BUF_COUNT);
}

GLInputLayout::~GLInputLayout()
{
	CH_SFDELARR(m_pLayouts);
}

inline uint GetValueTypeBytesSize(RVariableType::Type e)
{
	switch(e)
	{
	case RVariableType::VEC2:
		return sizeof(Vector2);
	case RVariableType::VEC3:
		return sizeof(Vector3);
	case RVariableType::VEC4:
		return sizeof(Vector4);
	default:
		CH_ASSERT(false,"[rd] error: unhandled enum type in function GetValueTypeBytesSize.");
		return 0;
	}
}


bool GLInputLayout::Init( IInputLayout::Desc *pLayoutArray,uint nLayoutCount)
{
	if(pLayoutArray==nullptr)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: input parameter pLayoutArray is null");
		return false;
	}

	int nSupportVACount = ((GLRenderDevice*)m_pRenderDevice)->GetSupportVertexAttributeCount();
	if(nLayoutCount==0 || nLayoutCount > (uint)nSupportVACount)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: input parameter nLayoutCount is invalid.  nLayoutCount=%d, current support count is %d",
				nLayoutCount,nSupportVACount);
		return false;
	}

	m_pLayouts = new IInputLayout::Desc[nLayoutCount];
	m_nLayoutCount = nLayoutCount;
	m_nVertexSize = 0;
	for(uint i=0; i<nLayoutCount; ++i)
	{
		m_pLayouts[i] = pLayoutArray[i];
		m_nVertexSize += GetValueTypeBytesSize(m_pLayouts[i].varType);

		//validate the layout parameter
		switch(m_pLayouts[i].vertexType)
		{
		case VertexType::POSITION:
		case VertexType::NORMAL:
		case VertexType::TEXCOORD:
			break;
		default:
			CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: the VertexType::Type enum is invalid!");
			return false;
		}

		switch(m_pLayouts[i].varType)
		{
		case RVariableType::BOOL:
			m_pEleCount[i] = 1;
			break;
		case RVariableType::BOOL2:
			m_pEleCount[i] = 2;
			break;
		case RVariableType::BOOL3:
			m_pEleCount[i] = 3;
			break;
		case RVariableType::BOOL4:
			m_pEleCount[i] = 4;
			break;
		case RVariableType::INT:
			m_pEleCount[i] = 1;
			break;
		case RVariableType::INT2:
			m_pEleCount[i] = 2;
			break;
		case RVariableType::INT3:
			m_pEleCount[i] = 3;
			break;
		case RVariableType::INT4:
			m_pEleCount[i] = 4;
			break;
		case RVariableType::FLOAT:
			m_pEleCount[i] = 1;
			break;
		case RVariableType::VEC2:
			m_pEleCount[i] = 2;
			break;
		case RVariableType::VEC3:
			m_pEleCount[i] = 3;
			break;
		case RVariableType::VEC4:
			m_pEleCount[i] = 4;
			break;
		default:
			CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: RVariableType::Type enum is invalid!");
			return false;
		}

		if(m_pLayouts[i].attributeSlot > (uint)nSupportVACount)
		{
			CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: input parameter m_pLayouts[i].attributeSlot is invalid.  m_pLayouts[i].attributeSlot=%d, current support count is %d",
				m_pLayouts[i].attributeSlot,nSupportVACount);
			return false;
		}

		if(m_pLayouts[i].aligenedByteOffset > nSupportVACount * sizeof(Vector4))
		{
			CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: the parameter m_pLayouts[i].aligenedByteOffset data must be wrong!");
			return false;
		}
	}

	return true;
}


uint GLInputLayout::GetDescCount() const
{
	return m_nLayoutCount;
}

const IInputLayout::Desc * GLInputLayout::GetDescArray() const
{
	return m_pLayouts;
}

bool GLInputLayout::ValidateInputLayout( GLShaderProgram *pProgram )
{
	if(pProgram==nullptr)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: input parameter pProgram is null");
		return false;
	}

	if(pProgram->GetActiveAttributeCount() != m_nLayoutCount)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: the input layout attribute count not equal to the shader program's attribute count.\n"
			"\t Shader has follow attributes:\n%s",pProgram->GetActiveAttributeInfos().c_str());
		return false;
	}

	for(uint i=0; i<m_nLayoutCount; ++i)
	{
		GLShaderVertexAttribute *pAttribute = (GLShaderVertexAttribute*)pProgram->GetVertexAttributeByIndex(i);
		if(m_pLayouts[i].varType != pAttribute->GetType())
		{
			CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: the input parameter's varType not math the shader program's attribute type")
				return false;
		}
	}

	return true;
}



NS_CH_END

