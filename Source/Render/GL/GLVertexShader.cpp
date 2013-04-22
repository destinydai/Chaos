#include "stdafx.h"


NS_CH_BEG


GLVertexShader::GLVertexShader( IRenderDevice *pDevice ):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1)
{

}

GLVertexShader::~GLVertexShader()
{

}

NS_CH_END