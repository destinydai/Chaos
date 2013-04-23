#include "stdafx.h"

#ifdef CH_PLATFORM_WINDOWS

	
NS_CH_BEG

GLEGL::GLEGL() : m_hWnd(NULL)
	, m_eglDisplay(EGL_NO_DISPLAY)
	, m_eglSurface(EGL_NO_SURFACE)
	, m_eglContext(EGL_NO_CONTEXT)
{

}


	GLEGL::~GLEGL()
{
	if (EGL_NO_SURFACE != m_eglSurface)
	{
		eglDestroySurface(m_eglDisplay, m_eglSurface);
	}
	if (EGL_NO_CONTEXT != m_eglContext)
	{
		eglDestroyContext(m_eglDisplay, m_eglContext);
	}

	eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(m_eglDisplay);

#ifdef CH_PLATFORM_WINDOWS
	if (m_hWnd)
	{
		ReleaseDC(m_hWnd, m_hdc);
	}
#endif
}

GLEGL * GLEGL::Create( void* hWnd )
{
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

	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	EGLContext context;
	EGLSurface surface;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// Get Display
	display = eglGetDisplay(GetDC((HWND)hWnd));
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

	// Create a surface
	surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)hWnd, NULL);
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
		return nullptr;
	}

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
	CH_ASSERT(szInfo);
	return (const char*)szInfo;
}


NS_CH_END

#endif //#endif