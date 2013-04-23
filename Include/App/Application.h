#pragma once


NS_CH_BEG

class Application
{
public:
	typedef void (*pfn_OnIdle)(void *pUserParm);
	typedef bool (*pfn_OnRenderDeviceCreated)(IRenderDevice* pRender);
protected:
	Application(void);
	virtual ~Application(void);
public:
	static Application *GetInstancePtr(); 
	IRenderDevice *GetRenderDevice() { return m_pRenderDevice; }
	Window* GetWindow() { return m_pWindows; }

	virtual void SetOnIdleProc(pfn_OnIdle onIdle,void *pUserParm)=0;
	virtual void SetOnRenderDeviceCreated(pfn_OnRenderDeviceCreated onRenderCreated)=0;
	virtual bool Create(uint nWidth,uint nHeight)=0;
	virtual void Close()=0;
	virtual void Run(void)=0;
protected:
	IRenderDevice *m_pRenderDevice;
	Window *m_pWindows;
};

NS_CH_END
