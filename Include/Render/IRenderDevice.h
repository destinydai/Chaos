#pragma once


NS_CH_BEG

namespace RenderDriverType
{
	enum Type
	{
		OPENGL
	};
}


namespace ShaderType
{
	enum Type
	{
		UNKNOW,
		VERTEX,
		PIXEL
	};
}


namespace PrimitiveType
{
	enum Type
	{
		POINT_LIST,
		LINE_LIST,
		LINE_STRIP,
		TRIANGLE_LIST,
		TRIANGLE_STRIP
	};
}

namespace RVariableType
{
	enum Type
	{
		UNKNOW=0,
		BOOL,
		BOOL2,
		BOOL3,
		BOOL4,
		UNSIGNED_BYTE,
		UNSIGNED_SHORT,
		UNSIGNED_INT,
		INT,
		INT2,
		INT3,
		INT4,
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
		SAMPLER_2D,
		SAMPLER_CUBE,

		VEC2_ARRAY,
		VEC3_ARRAY,
		VEC4_ARRAY,
		MAT2_ARRAY
	};
}

namespace VertexType
{
	enum Type
	{
		POSITION,
		NORMAL,
		TEXCOORD,
	};
}

namespace RasterizerFlag
{
	enum FillMode
	{
		FILL_WAREFRAME=2,
		FILL_SOLID=3,
	};

	enum CullMode
	{
		CULL_NONE=1,
		CULL_FRONT=2,
		CULL_BACK=3
	};
}

namespace ColorFormat
{
	enum Type
	{
		RGB,
		RGBA,
		LUMINANCE,
		LUMINANCE_ALPHA,
		ALPHA
	};
}

namespace TextureWrapMode
{
	enum Mode
	{
		REPEAT,
		CLAMP_TO_EDGE,
		MIRRORED_REPEAT
	};
}


struct Viewport
{
	int lbX,lbY;
	int width,height;
	float minDepth,maxDepth;
};

class IRenderDevice;

class IRenderBase
{
public:
	virtual void AddRef()=0;
	virtual void DeRef() =0;
	virtual int GetRef() const =0;
	virtual IRenderDevice* GetDevice() =0;
	virtual void SetUserData(void *pData)=0;
	virtual void* GetUserData()=0;
};

class IVertexShader : public IRenderBase
{

};

class IPixelShader : public IRenderBase
{

};

class IDepthStencilState : public IRenderBase
{

};

class IBlendState : public IRenderBase
{

};

class IRasterizerState : public IRenderBase
{
public:
	struct Parm
	{
		RasterizerFlag::FillMode fillMode;
		RasterizerFlag::CullMode cullMode;
		bool frontCounterClockwise;
		int depthBias;
		float DepthBiasClamp;
		float slopeScaledDepthBias;
		bool depthClipEnable;
		bool scissorEnable;
		bool multisampleEnable;
		bool antialiasedLineEnable;
	};

	virtual void GetParm(IRasterizerState::Parm *pParm) =0;
};


class IInputLayout : public IRenderBase
{
public:
	struct Desc
	{
		VertexType::Type vertexType;
		RVariableType::Type varType;
		uint attributeSlot;
		uint aligenedByteOffset;
		Desc():vertexType(VertexType::POSITION),varType(RVariableType::VEC3),attributeSlot(0),aligenedByteOffset(0){}
	};
public:
	virtual uint GetDescCount() const=0;
	virtual const IInputLayout::Desc *GetDescArray() const=0;
};

class IRenderResource : public IRenderBase
{
public:
	enum Usage
	{
		IMMUTABLE,				//the application will not alert the buffer
		DYNAMIC,					//the application may usually update the buffer content
	};

	enum BindFlag
	{
		VERTEX_BUFFER= 1,						//the buffer use as a vertex buffer used in vertex shader
		INDEX_BUFFER = 1<<1,					//the buffer use as a index buffer used in vertex shader
		CONSTANT_BUFFER	 = 1<<2,
		SHADER_RESOURCE = 1<<3,
		RENDER_TARGET = 1<<4
	};

	struct InitData
	{
		const void *pSysMem;							//the data use to fill the buffer
		uint sysMemPitch;									
		uint sysMemSlicePitch;

		InitData():pSysMem(0),sysMemPitch(0),sysMemSlicePitch(0){}

		InitData(const void *_pSysMem,uint _sysMemPitch,uint _sysMemSlicePitch):
		pSysMem(_pSysMem),sysMemPitch(_sysMemPitch),sysMemSlicePitch(_sysMemSlicePitch){}

	};
};

class ITexture2D : public IRenderResource
{
public:
	struct Desc
	{
		uint width;
		uint height;
		uint mipLevels;
		uint arraySize;
		ColorFormat::Type format;
		IRenderResource::Usage usage;
		IRenderResource::BindFlag bindFlags;
	};
};

class IRenderBuffer : public IRenderResource
{
public:
	struct Desc
	{
		uint bytes;												//the buffer size
		IRenderResource::Usage usage;				
		IRenderResource::BindFlag bindFlag;		
		Desc():bytes(0),usage(IMMUTABLE),bindFlag((BindFlag)0){}
	};

public:
	virtual void GetDesc(IRenderBuffer::Desc *pDesc)=0;
};

class IShaderVariable
{
public:
	virtual RVariableType::Type GetVariableType() const =0;
	virtual const char *GetVariableName() const=0;

	virtual uint GetVariableCount() const =0;

	virtual void SetFloat(const float *pValue,uint nCount)=0;
	virtual void SetInt(const int32 *pValue,uint nCount)=0;
	virtual void SetBool(const boolean *pValue,uint nCount)=0;

	virtual void SetVector2(const Vector2 *pVectors,uint nCount)=0;
	virtual void SetVector3(const Vector3 *pVectors,uint nCount)=0;
	virtual void SetVector4(const Vector4 *pVectors,uint nCount)=0;
	virtual void SetInt2(const int *pIntegers,uint nCount)=0;
	virtual void SetInt3(const int *pIntegers,uint nCount)=0;
	virtual void SetInt4(const int *pIntegers,uint nCount)=0;

	virtual void SetMatrix2(const Matrix2 *pMatrixes,uint nCount)=0;
	virtual void SetMatrix3(const Matrix3 *pMatrixes,uint nCount)=0;
	virtual void SetMatrix4(const Matrix4 *pMatrixes,uint nCount)=0;

	virtual void SetTexture2D(uint slot,ITexture2D *pTexture)=0;
};

class IShaderVertexAttribute
{
public:
	virtual const char *GetName() const=0;
	virtual uint GetIndex() const=0;
	virtual RVariableType::Type GetType() const =0;
};

class IShaderProgram : public IRenderBase 
{
public:
	virtual void SetDepthStencilState(IDepthStencilState *pState) =0;
	virtual void SetBlendState(IBlendState *pState)=0;
	virtual void SetRasterizerState(IRasterizerState *pState) =0;
	virtual IDepthStencilState* GetDepthStencilState()=0;
	virtual IBlendState* GetBlendState()=0;
	virtual IRasterizerState* GetRasterizerState()=0;

	virtual IShaderVariable *GetVariableByName(const char *szVariableName)=0;
	virtual IShaderVariable *GetVariableByIndex(uint index)=0;
	virtual uint GetVariableCount() const =0;

	virtual IShaderVertexAttribute *GetVertexAttributeByName(const char *szName)=0;
	virtual IShaderVertexAttribute *GetVertexAttributeByIndex(uint index)=0;
	virtual uint GetVertexAttributeCount() const =0;

	//display shader program vertex attribute and variable information
	virtual string ToString()=0;

	virtual int GetProgramID() =0;
};

class IRenderDevice 
{
public:

	virtual void SwapBuffer()=0;

	virtual void SetShaderProgram(IShaderProgram *pShaderProgram)=0;

	virtual void Draw(PrimitiveType::Type ePrimitiveType,uint nVertexCount,uint nStartVertexLocation)=0;

	virtual  void DrawIndexed(PrimitiveType::Type ePrimitiveType,uint nIndexCount,uint nStartIndexLocation) =0;

	virtual void SetVertexBuffers(IRenderBuffer **ppBuffers,uint nBufferCount)=0;

	virtual void SetIndexBuffer(IRenderBuffer *pIndexBuffer,RVariableType::Type eIndexType,uint offset)=0;

	virtual bool SetVertexLayout(IInputLayout *pLayout) =0;

	virtual void ClearBuffer(bool color, bool depth, bool stencil)=0;

	virtual void SetViewport(int x,int y,int nWidth, int nHeight)=0;
	virtual Viewport GetViewport()=0;

	virtual void ClearState(void)=0;

	virtual void Flush() =0;

	virtual IRenderBuffer *CreateBuffer(IRenderBuffer::Desc *pDesc, IRenderBuffer::InitData *pInitData)=0;

	virtual IInputLayout* CreateInputLayout(IInputLayout::Desc *pLayoutArray,uint nLayoutCount,IShaderProgram *pProgram)=0;

	virtual IVertexShader* CreateVertexShader(const char *pCode,uint nCodeLen)=0;

	virtual IPixelShader* CreatePixelShader(const char *pCode,uint nCodeLen)=0;

	virtual IShaderProgram* CreateShaderProgram(IVertexShader *pVShader,IPixelShader *pPShader)=0;

	virtual ITexture2D* CreateTexture2D(const ITexture2D::Desc* pDesc,const IRenderResource::InitData* pInitData)=0;

	virtual ITexture2D* CreateTexture2D(const char *szFilePath)=0;

	virtual void SetWorldMatrix(const Matrix4 &m)=0;

	virtual void SetViewMatrix(const Matrix4 &m)=0;

	virtual void SetProjectionMatrix(const Matrix4 &m)=0;

	virtual const Matrix4 &GetWorldMatrix() const=0;

	virtual const Matrix4 &GetViewMatrix() const=0;

	virtual const Matrix4 &GetProjectionMatrix() const=0;

	virtual RenderDriverType::Type GetAPIType() const =0;

	virtual int GetWidth()const=0;

	virtual int GetHeight()const=0;

	virtual void SetClearColor(Color3 color)=0;
	virtual Color3 GetClearColor() const=0;

	virtual void SetClearDepth(float value)=0;
	virtual float GetClearDepth() const=0;

	virtual void SetClearStencil(int value)=0;
	virtual int GetClearStencil() const=0;

	virtual const char *GetErrorMessage() const =0;

	virtual bool HasError() const =0; 

	virtual void Release()=0;
};


IRenderDevice *CreateRenderDevice(void *winID,int nWidth,int nHeight,RenderDriverType::Type eType,bool bWindowed=true);

NS_CH_END