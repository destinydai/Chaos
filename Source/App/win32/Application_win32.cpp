
NS_CH_BEG

Application::Application( void ):
	m_pWindows(nullptr),
	m_pRenderDevice(nullptr)
{
	
}

Application::~Application( void )
{
	CH_SFDEL(m_pWindows);

	if(m_pRenderDevice)
	{
		m_pRenderDevice->Release();
		m_pRenderDevice=nullptr;
	}

	
}

bool Application::Create( const wchar *szWinTitle,uint nWidth,uint nHeight )
{
	if(nullptr == m_pInstance)
	{
		m_pInstance = new Application();
	}

	GetInstancePtr()->m_pWindows = new Win32Window();
	if(!GetInstancePtr()->m_pWindows->Create(szWinTitle,nWidth,nHeight))
	{
		CH_TRACE("[pl] error: create window failed.");
		return false;
	}

		GetInstancePtr()->m_pRenderDevice = CreateRenderDevice(GetInstancePtr()->m_pWindows->GetWind(),RenderDriverType::OPENGL,true);
	if(GetInstancePtr()->GetRenderDevice() == nullptr)
		return false;

	return true;
}

void Application::Run( void )
{
	if(m_pWindows==nullptr)
		return;

	m_pWindows->Run();
}

void Application::SetOnIdleProc( pfn_OnIdle onIdle,void *pUserParm )
{
	if(m_pWindows == nullptr)
		return ;
	
	m_pWindows->SetOnIdleEvent(onIdle,pUserParm);
}

void Application::Close()
{
	if(m_pWindows)
	{
		m_pWindows->Close();
	}
}

void Application::Destroy( void )
{
	CH_SFDEL(m_pInstance);
}

Application * Application::m_pInstance;

NS_CH_END

