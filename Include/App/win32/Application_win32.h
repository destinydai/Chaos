#pragma once



NS_CH_BEG

class Application
{
public:
	typedef void (*pfn_OnIdle)(void *pUserParm);
protected:
	Application(void);
	virtual ~Application(void);
public:
	static bool Create(const wchar *szWinTitle,uint nWidth,uint nHeight);
	static void Destroy(void);
	static Application *GetInstancePtr() { return m_pInstance; } 

	void SetOnIdleProc(pfn_OnIdle onIdle,void *pUserParm);

	IRenderDevice *GetRenderDevice() { return m_pRenderDevice; }

	void Close();
public:
	void Run(void);

private:
	IRenderDevice *m_pRenderDevice;
	static Application *m_pInstance;

	//win32 specific 
	Win32Window *m_pWindows;
};


NS_CH_END