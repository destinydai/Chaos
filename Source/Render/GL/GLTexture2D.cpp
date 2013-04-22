#include "stdafx.h"


NS_CH_BEG

GLTexture2D::GLTexture2D( GLRenderDevice *pDevice ):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1),
	m_objID(0)
{
	
}

GLTexture2D::~GLTexture2D( void )
{
	Reset();
}

bool GLTexture2D::Init( const ITexture2D::Desc *pDesc,const IRenderResource::InitData *pInitData)
{
	if(pDesc ==nullptr || pInitData == nullptr)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: both pDesc and pInitData can not be null.");
		return false;
	}

	Reset();

	glGenTextures(1,&m_objID);
	if(m_objID==0)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"[rd] error: create texture object unexpected failed. gl error code %d",glGetError());
		return false;
	}

	m_desc = *pDesc;
	if(m_desc.usage == IRenderResource::IMMUTABLE && pInitData == nullptr)
	{
		CH_RENDER_TRACE_ERROR(GetDevice(),"the resource usage is immutable, so you must fill the resouce data on create it. please set the IRenderResource::InitData parm.");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D,m_objID);
	GLenum eGlColorType = MapColorFormatToGLColor(pDesc->format);
	
	glTexImage2D(GL_TEXTURE_2D, 0, eGlColorType, pDesc->width, pDesc->height, 0, eGlColorType,GL_UNSIGNED_BYTE, pInitData->pSysMem);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);


	return true;
}

void GLTexture2D::Reset()
{
	if(m_objID)
	{
		glDeleteTextures(1,&m_objID);
		m_objID=0;
	}
}

NS_CH_END