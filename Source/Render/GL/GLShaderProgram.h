#pragma once


NS_CH_BEG

class GLShaderVariable;


class GLShaderVertexAttribute;


class GLShaderProgram : public IShaderProgram
{
	CH_IMPL_RENDER_BASE
public:
	GLShaderProgram(IRenderDevice *pDevice);
	virtual ~GLShaderProgram();
public:
	bool Compile(GLVertexShader *pVShader,GLPixelShader *pPShader);
	inline int GetActiveAttributeCount() const { return m_nAttributeCount; }
	
	inline int GetActiveUniformsCount() const { return m_nUniformCount; }

	inline GLint GetShaderProgramID() const { return m_nProgramID; }
	
	inline GLShaderVariable *GetGLShaderVariableByIndex(uint index) { return m_ppShaderVariable[index]; }

	string GetActiveUniformInfos() ;

	string GetActiveAttributeInfos() ;

public://interface
	void SetDepthStencilState(IDepthStencilState *pState) ;
	void SetBlendState(IBlendState *pState);
	void SetRasterizerState(IRasterizerState *pState) ;
	IDepthStencilState* GetDepthStencilState();
	IBlendState* GetBlendState();
	IRasterizerState* GetRasterizerState();

	IShaderVariable *GetVariableByName(const char *szVariableName);
	IShaderVariable *GetVariableByIndex(uint index);
	uint GetVariableCount() const;

	IShaderVertexAttribute *GetVertexAttributeByName(const char *szName);
	IShaderVertexAttribute *GetVertexAttributeByIndex(uint index);
	uint GetVertexAttributeCount() const;

	string ToString();

	int GetProgramID() { return m_nProgramID; }
private:
	bool ObtainShaderProperty();
	void ReleaseMember();
protected:
	GLint m_nProgramID;

	GLShaderVariable **m_ppShaderVariable;

	GLShaderVertexAttribute **m_ppShaderVertexAttribute;

	int m_nAttributeCount;
	
	int m_nUniformCount;
};


NS_CH_END