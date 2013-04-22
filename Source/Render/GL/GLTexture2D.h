#pragma once


NS_CH_BEG

class GLTexture2D : public ITexture2D
{
	CH_IMPL_RENDER_BASE
public:
	GLTexture2D(GLRenderDevice *pDevice);
	virtual ~GLTexture2D(void);
public:
	GLuint GetID() const { return m_objID; }

	bool Init(const ITexture2D::Desc *pDesc,const IRenderResource::InitData *pInitData);

private:
	void Reset();
private:
	ITexture2D::Desc m_desc;
	GLuint m_objID;
};


NS_CH_END