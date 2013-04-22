#include "stdafx.h"


NS_CH_BEG

GLRenderBuffer::GLRenderBuffer( IRenderDevice *pDevice ):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1),
	m_bufID(0)
{
	
}

GLRenderBuffer::~GLRenderBuffer( void )
{
	if(m_bufID)
	{
		glDeleteBuffers(1,&m_bufID);
		m_bufID=0;
	}
}

bool GLRenderBuffer::Init( IRenderBuffer::Desc *pDesc,IRenderBuffer::InitData *pInitData )
{
	glGenBuffers(1,&m_bufID);
	if(m_bufID==0)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: call glGenBuffers to create buffer unexpected failed. code:",glGetError());
		return false;
	}

	m_desc = *pDesc;
	GLuint bindSlot=0;
	GLint bufUsage = 0;
	switch(m_desc.bindFlag)
	{
	case IRenderBuffer::VERTEX_BUFFER:
		bindSlot = GL_ARRAY_BUFFER;
		break;
	case IRenderBuffer::INDEX_BUFFER:
		bindSlot = GL_ELEMENT_ARRAY_BUFFER;
		break;
	default:
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: invalid IRenderBuffer::BindFlag enum.  enum:%d",m_desc.bindFlag);
		return false;
	}

	switch(pDesc->usage)
	{
	case IRenderBuffer::IMMUTABLE:
		bufUsage = GL_STATIC_DRAW;
		break;
	case IRenderBuffer::DYNAMIC:
		bufUsage = GL_DYNAMIC_DRAW;
		break;
	default:
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: invalid IRenderBuffer::Usage enum.  enum:%d",m_desc.bindFlag);
		return false;
	}

	glBindBuffer(bindSlot,m_bufID);
	glBufferData(bindSlot,pDesc->bytes,pInitData->pSysMem,bufUsage);
	glBindBuffer(bindSlot,0);
	CH_GLFAILCHECK;

	return true;
}

void GLRenderBuffer::GetDesc( IRenderBuffer::Desc *pDesc )
{
	*pDesc = m_desc;
}

NS_CH_END