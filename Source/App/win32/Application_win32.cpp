#include "stdafx.h"
#include "App/win32/Application_win32.h"

NS_CH_BEG

Application_win32::Application_win32( void ):
	m_OnRenderDeviceCreated(nullptr),
	m_pUserData(nullptr),
	m_OnIdle(nullptr)
{
	
}

Application_win32::~Application_win32( void )
{
	Win32Window* pWnd = (Win32Window*)m_pWindows;
	CH_SFDEL(pWnd);
	m_pWindows = nullptr;
}

bool Application_win32::Create(uint nWidth,uint nHeight )
{
	m_pWindows = new Win32Window();
	if(!GetWin32Window()->Create(L"Chaos3D",nWidth,nHeight))
	{
		CH_TRACE("[pl] error: create window failed.");
		return false;
	}

	GetWin32Window()->SetOnIdleEvent(m_OnIdle,m_pUserData);

	m_pRenderDevice = CreateRenderDevice(GetWin32Window()->GetWind(),RenderDriverType::OPENGL,true);
	if(m_pRenderDevice== nullptr)
		return false;

	if(m_OnRenderDeviceCreated)
	{
		m_OnRenderDeviceCreated(m_pRenderDevice);
	}

	return true;
}

void Application_win32::Run( void )
{
	if(m_pWindows==nullptr)
		return;

	GetWin32Window()->Run();
}

void Application_win32::SetOnIdleProc( pfn_OnIdle onIdle,void *pUserParm )
{
	m_OnIdle = onIdle;
	m_pUserData = pUserParm;

	if(GetWin32Window())
		GetWin32Window()->SetOnIdleEvent(onIdle,pUserParm);
}

void Application_win32::Close()
{
	if(m_pWindows)
	{
		GetWin32Window()->Close();
	}
}

NS_CH_END

