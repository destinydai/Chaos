#pragma once


NS_CH_BEG

class GraphicsManager 
{
protected:
	GraphicsManager(IRenderDevice *pDevice);
	virtual ~GraphicsManager(void);
public:
	static void Create(IRenderDevice *pDevice);
	static void Destroy(void);
	static GraphicsManager *GetInstancePtr() 
	{ CH_ASSERT(m_pInstance); return m_pInstance; } 

	inline void SetRenderDevice(IRenderDevice *pDevice) { m_pRender = pDevice; }
	inline IRenderDevice *GetRenderDevice() { return m_pRender; }


protected:

	IRenderDevice *m_pRender;

	static GraphicsManager *m_pInstance;
};

NS_CH_END