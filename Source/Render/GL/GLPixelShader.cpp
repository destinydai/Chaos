#include "stdafx.h"


NS_CH_BEG


GLPixelShader::GLPixelShader(IRenderDevice *pDevice):
	m_pRenderDevice(pDevice),
	m_pUserData(nullptr),
	m_nRefCount(1)
{

}

GLPixelShader::~GLPixelShader()
{

}

NS_CH_END