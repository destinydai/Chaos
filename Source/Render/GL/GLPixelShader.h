#pragma once


NS_CH_BEG

class GLPixelShader : public GLShader, public IPixelShader
{
	CH_IMPL_RENDER_BASE
public:
	GLPixelShader(IRenderDevice *pDevice); 
	virtual ~GLPixelShader();

	
};

NS_CH_END