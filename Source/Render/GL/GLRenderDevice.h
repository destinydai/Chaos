#pragma once


NS_CH_BEG

class GLInputLayout;
class GLRenderBuffer;

class GLRenderDevice : public RenderDevice 
{
public:
	enum 
	{
		INPUT_VERTEX_BUF_COUNT=8
	};
public:
	GLRenderDevice();
	virtual ~GLRenderDevice();

	virtual void AfterDeviceCreated();

public://interface

	void SetShaderProgram(IShaderProgram *pShaderProgram);

	void Draw(PrimitiveType::Type ePrimitiveType,uint nVertexCount,uint nStartVertexLocation);

	 void DrawIndexed(PrimitiveType::Type ePrimitiveType,uint nIndexCount,uint nStartIndexLocation) ;

	void SetVertexBuffers(IRenderBuffer **ppBuffers,uint nBufferCount);

	void SetIndexBuffer(IRenderBuffer *pIndexBuffer,RVariableType::Type eIndexType,uint offset);

	bool SetVertexLayout(IInputLayout *pLayout) ;

	void ClearBuffer(bool color, bool depth, bool stencil);

	void SetViewport(int x,int y,int nWidth, int nHeight);
	Viewport GetViewport();

	void SetClearColor(Color3 color);
	void SetClearDepth(float value);
	void SetClearStencil(int value);

	RenderDriverType::Type GetAPIType() const { return RenderDriverType::OPENGL; }

	void ClearState(void);

	void Flush() ;

	IRenderBuffer *CreateBuffer(IRenderBuffer::Desc *pDesc, IRenderBuffer::InitData *pInitData);

	IInputLayout* CreateInputLayout(IInputLayout::Desc *pLayoutArray,uint nLayoutCount,IShaderProgram *pProgram);

	IVertexShader* CreateVertexShader(const char *pCode,uint nCodeLen);

	IPixelShader* CreatePixelShader(const char *pCode,uint nCodeLen);

	IShaderProgram* CreateShaderProgram(IVertexShader *pVShader,IPixelShader *pPShader);

	ITexture2D* CreateTexture2D(const ITexture2D::Desc* pDesc,const IRenderResource::InitData* pInitData);

	ITexture2D* CreateTexture2D(const char *szFilePath);

public://inner use

	inline uint GetSupportVertexAttributeCount() const { return 8; }

	inline GLEGL* GetEGL() { return m_pEGL; }
protected:
	GLShaderProgram *m_pShaderProgram;
	GLInputLayout *m_pAttributeLayout;

	GLRenderBuffer *m_pIndexBuffer;
	GLenum m_eIndexType;
	uint m_nIndexOffset;

	GLRenderBuffer* m_ppVertexBuffers[INPUT_VERTEX_BUF_COUNT];
	uint m_nVertexBufferCount;
	
};

NS_CH_END