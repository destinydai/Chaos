#pragma once


NS_CH_BEG

class GLShaderProgram;

class GLShaderVariable : public IShaderVariable
{
public:
	GLShaderVariable(IRenderDevice *pDevice,GLShaderProgram *pProgram,GLint nUniformLocation,
		RVariableType::Type eVarType,const char *szName,uint nArraySize);
	virtual ~GLShaderVariable(void);

	IRenderDevice *GetDevice() { return m_pRenderDevice; }

public://interface
	RVariableType::Type GetVariableType() const ;
	const char *GetVariableName() const;

	uint GetVariableCount() const ;

	void SetFloat(const float *pValue,uint nCount);
	void SetInt(const int32 *pValue,uint nCount);
	void SetBool(const boolean *pValue,uint nCount);

	void SetVector2(const Vector2 *pVectors,uint nCount);
	void SetVector3(const Vector3 *pVectors,uint nCount);
	void SetVector4(const Vector4 *pVectors,uint nCount);
	void SetInt2(const int *pIntegers,uint nCount);
	void SetInt3(const int *pIntegers,uint nCount);
	void SetInt4(const int *pIntegers,uint nCount);

	void SetMatrix2(const Matrix2 *pMatrixes,uint nCount);
	void SetMatrix3(const Matrix3 *pMatrixes,uint nCount);
	void SetMatrix4(const Matrix4 *pMatrixes,uint nCount);

	void SetTexture2D(uint slot,ITexture2D *pTexture);
private:
	IRenderDevice *m_pRenderDevice;
	GLShaderProgram *m_pShaderProgram;
	GLint m_nUnifornLocation;
	RVariableType::Type m_varType;
	char *m_szVarName;
	uint m_nArraySize;

};

NS_CH_END