#pragma once


NS_CH_BEG

class GLRenderBase : public IVertexShader, public IPixelShader, public IShaderProgram 
{
public:
	GLRenderBase(IRenderDevice *pDevice);
	virtual ~GLRenderBase();

public://interface
	void AddRef() {++m_nRefCount;}
	void DeRef() { --m_nRefCount;}
	void SetRef(int nRef) { m_nRefCount=nRef;}
	int GetRef() const { return m_nRefCount; };

	IRenderDevice* GetDevice(){ return m_pRenderDevice; };

	void SetUserData(void *pData) { m_pUserData=pData; }

	void* GetUserData() { return m_pUserData; }

	void Release() { delete this;}
private:
	IRenderDevice *m_pRenderDevice;
	void *m_pUserData;
	int m_nRefCount;
};



NS_CH_END