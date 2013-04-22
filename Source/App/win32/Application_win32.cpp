#include "stdafx.h"
#include "App/win32/Application_win32.h"

NS_CH_BEG

Application_win32::Application_win32( void )
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

	m_pRenderDevice = CreateRenderDevice(GetWin32Window()->GetWind(),RenderDriverType::OPENGL,true);
	if(m_pRenderDevice== nullptr)
		return false;

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
	if(m_pWindows == nullptr)
		return ;
	
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

