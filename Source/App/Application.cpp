#include "stdafx.h"

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#include "App/win32/Application_win32.h"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include "App/win32/Application_win32.h"
#else
CH_ERROR("not implement yet");
#endif

NS_CH_BEG

Application::Application( void ):
	m_pWindows(nullptr),
	m_pRenderDevice(nullptr)
{

}

Application::~Application( void )
{
	if(m_pRenderDevice)
	{
		m_pRenderDevice->Release();
		m_pRenderDevice=nullptr;
	}
}


Application * Application::GetInstancePtr()
{
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	static Application_win32 instance;
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	static Application_android instance;
#else
	CH_ERROR("not implement yet");
#endif
	return &instance;
}

NS_CH_END

