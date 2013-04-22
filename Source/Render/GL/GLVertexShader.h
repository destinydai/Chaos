#pragma once


NS_CH_BEG

class GLVertexShader : public GLShader ,public IVertexShader
{
	CH_IMPL_RENDER_BASE
public:
	GLVertexShader(IRenderDevice *pDevice);
	virtual ~GLVertexShader();

	//CH_IMPL_RENDER_BASE
};

NS_CH_END