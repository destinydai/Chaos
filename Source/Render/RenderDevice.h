#pragma once


NS_CH_BEG

class GLEGL;
class RenderDevice : public IRenderDevice
{
public:
	RenderDevice();
	virtual ~RenderDevice();
public:
	bool Init(void* hWnd,bool bWindowed);

	virtual void AfterDeviceCreated() {}
public://interface

	void SwapBuffer();

	void SetWorldMatrix(const Matrix4 &m);

	void SetViewMatrix(const Matrix4 &m);

	void SetProjectionMatrix(const Matrix4 &m);

	const Matrix4 &GetWorldMatrix() const;

	const Matrix4 &GetViewMatrix() const;

	const Matrix4 &GetProjectionMatrix() const;

	int GetWidth()const;
	int GetHeight()const;

	Color3 GetClearColor() const;
	float GetClearDepth() const;
	int GetClearStencil() const;

	const char *GetErrorMessage() const ;

	bool HasError() const ; 

	void Release() { delete this; }
public://inner use
	void SetErrorMessage(const char *szInfo,...);
protected:
	Matrix4 m_mWorldMatrix;
	Matrix4 m_mViewMatrix;
	Matrix4 m_mProjectionMatrix;

	int m_nWidth,m_nHeight;
	Color3 m_clearColor;
	float m_clearDepth;
	int m_clearStencil;

	char *m_pErrorMessage;

	GLEGL *m_pEGL;
};

NS_CH_END
