#pragma once



NS_CH_BEG

class GLEGL
{
private:
	GLEGL();
public:
	~GLEGL();

	static GLEGL * Create( void* hWnd, int nWidth, int nHeight);

	void SwapBuffers();

	const char *GetVendor() const;
	const char *GetRenderer() const;
	const char *GetVersion() const;
	const char *GetShadingLanguageVersion() const;

	int GetWidth() const { return m_nWidth; }
	int GetHeight() const { return m_nHeight; }

private:
	EGLDisplay m_eglDisplay;
	EGLContext m_eglContext;
	EGLSurface m_eglSurface;
	int m_nWidth, m_nHeight;

	EGLNativeWindowType m_hWnd;
	EGLNativeDisplayType m_hdc;
};

NS_CH_END
