#include "stdafx.h"


#if CH_PLATFORM == CH_PLATFORM_ANDROID

NS_CH_BEG

GLEGL::GLEGL():m_eglContext(nullptr),
	m_eglDisplay(nullptr),
	m_eglSurface(nullptr),
	m_nHeight(0),
	m_nWidth(0)
{

}

GLEGL::~GLEGL()
{
	
}

GLEGL * GLEGL::Create( void* hWnd )
{
	NativeWindow_android* pWnd = (NativeWindow_android*)hWnd;
	GLEGL * pEGL = new GLEGL;

	EGLint attribList[] =
	{
		EGL_RED_SIZE,       8,
		EGL_GREEN_SIZE,     8,
		EGL_BLUE_SIZE,      8,
		EGL_ALPHA_SIZE,    8 ,
		EGL_DEPTH_SIZE,    8,
		EGL_STENCIL_SIZE,   8,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};

	//EGLint format;
	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// Get Display
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if ( display == EGL_NO_DISPLAY )
	{
		return nullptr;
	}

	// Initialize EGL
	if ( !eglInitialize(display, &majorVersion, &minorVersion) )
	{
		return nullptr;
	}
	CH_TRACE("[rd] egl version %d.%d",majorVersion,minorVersion);

	// Get configs
	if ( !eglGetConfigs(display, NULL, 0, &numConfigs) )
	{
		return nullptr;
	}

	// Choose config
	if ( !eglChooseConfig(display, attribList, &config, 1, &numConfigs) )
	{
		return nullptr;
	}

	//if(!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
	//{
	//	return nullptr;
	//}

	//ANativeWindow_setBuffersGeometry(pWnd->GetNativeWindow(), 0, 0, format);

	// Create a surface
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)pWnd->GetNativeWindow(), NULL);
	if ( surface == EGL_NO_SURFACE )
	{
		return nullptr;
	}

	// Create a GL context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs );
	if ( context == EGL_NO_CONTEXT )
	{
		return nullptr;
	}   

	// Make the context current
	if ( !eglMakeCurrent(display, surface, surface, context) )
	{
		 CH_ERROR("[rd] error:Unable to eglMakeCurrent");
		return nullptr;
	}

	eglQuerySurface(display,surface,EGL_WIDTH,&pEGL->m_nWidth);
	eglQuerySurface(display, surface,EGL_HEIGHT, &pEGL->m_nHeight);

	pEGL->m_eglDisplay = display;
	pEGL->m_eglSurface = surface;
	pEGL->m_eglContext = context;

	return pEGL;
}

void GLEGL::SwapBuffers()
{
	if (EGL_NO_DISPLAY != m_eglDisplay)
	{
		eglSwapBuffers(m_eglDisplay, m_eglSurface);
	}
}

const char * GLEGL::GetVendor() const
{
	const GLubyte *szInfo = glGetString(GL_VENDOR);
	CH_ASSERT(szInfo);
	return (const char*)szInfo;
}

const char * GLEGL::GetRenderer() const
{
	const GLubyte *szInfo = glGetString(GL_RENDERER);
	CH_ASSERT(szInfo);
	return (const char*)szInfo;
}

const char * GLEGL::GetVersion() const
{
	const GLubyte *szInfo = glGetString(GL_VERSION);
	CH_ASSERT(szInfo);
	return (const char*)szInfo;
}

const char * GLEGL::GetShadingLanguageVersion() const
{
	const GLubyte *szInfo = glGetString(GL_SHADING_LANGUAGE_VERSION);
	if(szInfo==nullptr)
	{
		CH_TRACE("[rd] error: call glGetString(GL_SHADING_LANGUAGE_VERSION) failed.");
	}
	return (const char*)szInfo;
}


NS_CH_END

#endif //CH_ANDROID