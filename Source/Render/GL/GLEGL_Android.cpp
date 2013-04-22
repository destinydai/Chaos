#include "stdafx.h"

#ifdef CH_ANDROID

NS_CH_BEG

GLEGL::GLEGL()
{

}

GLEGL::~GLEGL()
{
	
}

GLEGL * GLEGL::Create( void* hWnd )
{
	GLEGL * pEGL = new GLEGL;
	return pEGL;
}

void GLEGL::SwapBuffers()
{
	
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

#endif //CH_ANDROID