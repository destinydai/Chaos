#pragma once


NS_CH_BEG

class Application_win32 : public Application
{
public:
	Application_win32(void);
	virtual ~Application_win32(void);

private:
	inline Win32Window* GetWin32Window() { return (Win32Window*)m_pWindows; }

public:
	virtual void SetOnIdleProc(pfn_OnIdle onIdle,void *pUserParm);
	virtual void SetOnRenderDeviceCreated(pfn_OnRenderDeviceCreated onRenderCreated)
	{m_OnRenderDeviceCreated = onRenderCreated;}
	virtual bool Create(uint nWidth,uint nHeight);
	virtual void Close();
	virtual void Run(void);
private:
	pfn_OnRenderDeviceCreated m_OnRenderDeviceCreated;
	pfn_OnIdle m_OnIdle;
	void* m_pUserData;
};


NS_CH_END