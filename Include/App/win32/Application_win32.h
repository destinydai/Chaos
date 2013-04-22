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
	virtual bool Create(uint nWidth,uint nHeight);
	virtual void Close();
	virtual void Run(void);
};


NS_CH_END