#pragma once



NS_CH_BEG

class GLEGL
{
private:
	GLEGL();
public:
	~GLEGL();

	static GLEGL * Create(void* pWindow);

	void SwapBuffers();

	const char *GetVendor() const;
	const char *GetRenderer() const;
	const char *GetVersion() const;
	const char *GetShadingLanguageVersion() const;

private:
	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;

	EGLNativeWindowType m_hWnd;
	EGLNativeDisplayType m_hdc;
};

NS_CH_END
