#pragma once


NS_CH_BEG


class GLInputLayout : public IInputLayout
{
	CH_IMPL_RENDER_BASE
public:
	GLInputLayout(IRenderDevice *pDevice);
	virtual ~GLInputLayout();
public:
	bool Init(IInputLayout::Desc *pLayoutArray,uint nLayoutCount);
	inline uint GetLayoutCount() const { return m_nLayoutCount; }

	inline uint GetAttributeVertexSize() const { return m_nVertexSize; }

	inline const IInputLayout::Desc &GetDesc(uint index) const
	{ CH_ASSERT(index<m_nLayoutCount); return m_pLayouts[index]; }

	inline uint GetDescElementCount(uint index) const { return m_pEleCount[index]; }

	bool ValidateInputLayout(GLShaderProgram *pProgram);

public://interface
	uint GetDescCount() const;
	const IInputLayout::Desc *GetDescArray() const;
private:
	IInputLayout::Desc *m_pLayouts;
	uint m_nLayoutCount;
	uint m_pEleCount[GLRenderDevice::INPUT_VERTEX_BUF_COUNT];
	uint m_nVertexSize;
};



NS_CH_END