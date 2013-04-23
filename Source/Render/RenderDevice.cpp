#include "stdafx.h"

NS_CH_BEG

const uint CH_RENDER_ERROR_BUF_SIZE = 2048;

RenderDevice::RenderDevice():
	m_pErrorMessage(0),
	m_pEGL(0)
{
	m_mWorldMatrix = Math::mIdentity4;
	m_mViewMatrix = Math::mIdentity4;
	m_mProjectionMatrix = Math::mIdentity4;

	m_nWidth = 0;
	m_nHeight = 0;

	m_clearColor =Color3(0,0,0);
	m_clearDepth = 1.0f;
	m_clearStencil = 0;

	m_pErrorMessage=new char[CH_RENDER_ERROR_BUF_SIZE];
	memset(m_pErrorMessage,0,CH_RENDER_ERROR_BUF_SIZE);
}

RenderDevice::~RenderDevice()
{
	CH_SFDELARR(m_pErrorMessage);
	CH_SFDEL(m_pEGL);

	FreeImage_DeInitialise();
}

void RenderDevice::SetWorldMatrix( const Matrix4 &m )
{
	m_mWorldMatrix = m;
}

void RenderDevice::SetViewMatrix( const Matrix4 &m )
{
	m_mViewMatrix = m;
}

void RenderDevice::SetProjectionMatrix( const Matrix4 &m )
{
	m_mProjectionMatrix = m;
}

const Matrix4 &RenderDevice::GetWorldMatrix() const
{
	return m_mWorldMatrix;
}

const Matrix4 &RenderDevice::GetViewMatrix() const
{
	return m_mViewMatrix;
}

const Matrix4 &RenderDevice::GetProjectionMatrix() const
{
	return m_mProjectionMatrix;
}

const char * RenderDevice::GetErrorMessage() const
{
	return m_pErrorMessage;
}

bool RenderDevice::HasError() const
{
	return strlen(m_pErrorMessage)!=0;
}

void RenderDevice::SetErrorMessage(const char *szInfo, ... )
{
	va_list argList;
	va_start(argList,szInfo);
	vsprintf(m_pErrorMessage,szInfo,argList);
	va_end(argList);
}

int RenderDevice::GetWidth() const
{
	CH_ASSERT(false);
	return m_nWidth;
}

int RenderDevice::GetHeight() const
{
	CH_ASSERT(false);
	return m_nHeight;
}

Color3 RenderDevice::GetClearColor() const
{
	return m_clearColor;
}

float RenderDevice::GetClearDepth() const
{
	return m_clearDepth;
}
 

int RenderDevice::GetClearStencil() const
{
	return m_clearStencil;
}

static void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) 
{
	
	if(fif != FIF_UNKNOWN) 
	{
		CH_TRACE("[rd] freeimage error info:%s %s",message,FreeImage_GetFormatFromFIF(fif));
	}
	else
	{
		CH_TRACE("[rd] freeimage error info:%s unknow fif type.",message);
	}
}

bool RenderDevice::Init(void* hWnd,bool bWindowed )
{
	CH_ASSERT(m_pEGL==nullptr);
	m_pEGL = GLEGL::Create(hWnd) ;
	if(m_pEGL==nullptr)
	{
		return false;
	}

	CH_TRACE("[rd] Render device create complete:");
	CH_TRACE("[rd] Vendor:%s",m_pEGL->GetVendor());
	CH_TRACE("[rd] Renderer:%s",m_pEGL->GetRenderer());
	CH_TRACE("[rd] Version:%s",m_pEGL->GetVersion());
	const char* pShaderVersion = m_pEGL->GetShadingLanguageVersion();
	if(pShaderVersion)
	{
		CH_TRACE("[rd] Shading Language Version:%s",pShaderVersion);
	}
	else
	{
		CH_TRACE("[rd] Shading Language Version:%s","no version information");
	}
	
	
	FreeImage_Initialise(true);
	FreeImage_SetOutputMessage(FreeImageErrorHandler);


	AfterDeviceCreated();

	return true;
}

void RenderDevice::SwapBuffer()
{
	m_pEGL->SwapBuffers();
}

IRenderDevice * CreateRenderDevice(void *winID, RenderDriverType::Type eType,bool bWindowed)
{
	RenderDevice *pRenderDevice = nullptr;
	switch(eType)
	{
	case RenderDriverType::OPENGL:
		pRenderDevice = new GLRenderDevice();
		break;
	default:
		CH_TRACE("[rd] error invalid enum RenderDriverType::Type eType:%d",eType);
		return nullptr;
	}

	if(!pRenderDevice->Init(winID,bWindowed))
	{
		CH_SFDEL(pRenderDevice);
		return nullptr;
	}

	return pRenderDevice;
}

NS_CH_END
