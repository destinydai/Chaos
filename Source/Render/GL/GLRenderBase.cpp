#include "stdafx.h"


NS_CH_BEG

GLRenderBase::GLRenderBase( IRenderDevice *pDevice ):
	m_pRenderDevice(pDevice),m_pUserData(nullptr)
{

}

GLRenderBase::~GLRenderBase()
{

}

NS_CH_END