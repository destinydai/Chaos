#pragma once


NS_CH_BEG


class GLRenderBuffer : public IRenderBuffer
{
	CH_IMPL_RENDER_BASE
public:
	GLRenderBuffer(IRenderDevice *pDevice);
	virtual ~GLRenderBuffer(void);
public:
	bool Init(IRenderBuffer::Desc *pDesc,IRenderBuffer::InitData *pInitData);
	GLuint GetGLBufID() const { return m_bufID; }
	inline const IRenderBuffer::Desc &GetBufferDesc() const { return m_desc; }
public://interface 
	void GetDesc(IRenderBuffer::Desc *pDesc);
private:
	IRenderBuffer::Desc m_desc;
	GLuint m_bufID;
};

NS_CH_END