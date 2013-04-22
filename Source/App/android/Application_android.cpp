#include "stdafx.h"

NS_CH_BEG


Application::Application( void ):
	m_pRenderDevice(nullptr),
	m_onIdle(nullptr),
	m_pUserParm(nullptr)
{
	Tracer::Create();
}

Application::~Application( void )
{
	if(m_pRenderDevice)
	{
		m_pRenderDevice->Release();
		m_pRenderDevice=nullptr;
	}

	Tracer::Destroy();
}

bool Application::Create( const wchar *szWinTitle,uint nWidth,uint nHeight )
{
	if(nullptr == m_pInstance)
	{
		m_pInstance = new Application();
	}

	GetInstancePtr()->m_pRenderDevice = CreateRenderDevice(nullptr,RenderDriverType::OPENGL,true);
	if(GetInstancePtr()->GetRenderDevice() == nullptr)
		return false;

	return true;
}

void Application::Run( void )
{
	
}

void Application::SetOnIdleProc( pfn_OnIdle onIdle,void *pUserParm )
{
	m_onIdle = onIdle;
	m_pUserParm = pUserParm;
}

void Application::Close()
{
	
}

void Application::Destroy( void )
{
	CH_SFDEL(m_pInstance);
}

Application * Application::m_pInstance;

NS_CH_END

