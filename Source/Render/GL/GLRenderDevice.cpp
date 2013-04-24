#include "stdafx.h"
#include <fstream>


NS_CH_BEG

GLRenderDevice::GLRenderDevice():
	m_pShaderProgram(nullptr),
	m_pAttributeLayout(nullptr),
	m_pIndexBuffer(nullptr),
	m_eIndexType(RVariableType::UNKNOW),
	m_nIndexOffset(0),
	m_nVertexBufferCount(0)
{
	memset(m_ppVertexBuffers,0,sizeof(GLRenderBuffer*) * INPUT_VERTEX_BUF_COUNT);
}

GLRenderDevice::~GLRenderDevice()
{
	if(m_pIndexBuffer)
	{
		m_pIndexBuffer->DeRef();
		m_pIndexBuffer = nullptr;
	}

	for(uint i=0; i<m_nVertexBufferCount; ++i)
	{
		if(m_ppVertexBuffers[i])
		{
			m_ppVertexBuffers[i]->DeRef();
			m_ppVertexBuffers[i] = nullptr;
		}
	}

	if(m_pShaderProgram)
	{
		m_pShaderProgram->DeRef();
		m_pShaderProgram=nullptr;
	}

	if(m_pAttributeLayout)
	{
		m_pAttributeLayout->DeRef();
		m_pAttributeLayout = nullptr;
	}
}

void GLRenderDevice::ClearBuffer( bool color, bool depth, bool stencil )
{
	uint nMask = 0;
	if(color)
		nMask |= GL_COLOR_BUFFER_BIT;
	if(depth)
		nMask |= GL_DEPTH_BUFFER_BIT;
	if(stencil)
		nMask |= GL_STENCIL_BUFFER_BIT;
	glClear(nMask);
	CH_GLFAILCHECK;
}

void GLRenderDevice::SetViewport( int x,int y,int nWidth, int nHeight)
{
	glViewport(x,y,nWidth,nHeight);
	CH_GLFAILCHECK;
}

Viewport GLRenderDevice::GetViewport()
{
	CH_ASSERT(false);
	return Viewport();
}

void GLRenderDevice::ClearState( void )
{
	CH_ASSERT(false);
}

void GLRenderDevice::Flush()
{
	glFlush();
}

IVertexShader* GLRenderDevice::CreateVertexShader( const char *pCode,uint nCodeLen )
{
	GLVertexShader *pShader = new GLVertexShader(this);
	string szError = pShader->CreateFromMemory(pCode,nCodeLen,ShaderType::VERTEX);
	if(!szError.empty())
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error create vertex shader failed. error info:%s",szError.c_str());
		CH_SFDEL(pShader);
	}
	return pShader;
}

IPixelShader* GLRenderDevice::CreatePixelShader( const char *pCode,uint nCodeLen )
{
	GLPixelShader *pShader = new GLPixelShader(this);
	string szError = pShader->CreateFromMemory(pCode,nCodeLen,ShaderType::PIXEL);
	if(!szError.empty())
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error create pixel shader failed. error info:%s",szError.c_str());
		CH_SFDEL(pShader);
	}
	return pShader;
}

IShaderProgram* GLRenderDevice::CreateShaderProgram( IVertexShader *pVShader,IPixelShader *pPShader )
{
	GLVertexShader *pVGLShader = nullptr;
	GLPixelShader *pPGLShader = nullptr;

	pVGLShader = static_cast<GLVertexShader*>(pVShader);
	pPGLShader = static_cast<GLPixelShader*>(pPShader);

	GLShaderProgram *pProgram = new GLShaderProgram(this);
	
	if(!pProgram->Compile(pVGLShader,pPGLShader))
	{
		CH_SFDEL(pProgram);
	}

	return pProgram;
}

void GLRenderDevice::SetClearColor( Color3 color )
{
	glClearColor(color.r,color.g,color.b,1.0f);
	m_clearColor = color;
}

void GLRenderDevice::SetClearDepth( float value )
{
	glClearDepthf(value);
	m_clearDepth = value;
}

void GLRenderDevice::SetClearStencil( int value )
{
	glClearStencil(value);
	m_clearStencil = value;
}

inline GLenum GetGLValueType(IRenderDevice *pDevice, RVariableType::Type eType)
{
	switch(eType)
	{
	case RVariableType::FLOAT:
	case RVariableType::VEC2:
	case RVariableType::VEC3:
	case RVariableType::VEC4:
		return GL_FLOAT;
	case RVariableType::INT:
	case RVariableType::INT2:
	case RVariableType::INT3:
	case RVariableType::INT4:
		return GL_INT;
	default:
		CH_ASSERT(false,"[rd] error: GetGLValueType unhandled enum type.");
		return RVariableType::UNKNOW;
	}
}

void GLRenderDevice::Draw( PrimitiveType::Type ePrimitiveType,uint nVertexCount,uint nStartVertexLocation )
{
	if(m_nVertexBufferCount ==0 || m_ppVertexBuffers == nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the vertex buffer is not set, please set the vertex buffer before you call draw.");
		return;
	}

	if(m_pAttributeLayout == nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the input layout object is not set.");
		return;
	}

	GLRenderBuffer *pBuffer = nullptr;
	GLenum eGLValueType = 0;
	GLsizei stride =0;
	for(uint i=0; i<m_nVertexBufferCount; ++i)
	{
		pBuffer = m_ppVertexBuffers[i];
		eGLValueType = GetGLValueType(this,m_pAttributeLayout->GetDesc(i).varType);
		stride = m_pAttributeLayout->GetDesc(i).aligenedByteOffset;

		glBindBuffer(GL_ARRAY_BUFFER,pBuffer->GetGLBufID());
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,m_pAttributeLayout->GetDescElementCount(i),eGLValueType,false,stride,0);
	}

	glDrawArrays(MapPrimitiveTypeToGLType(ePrimitiveType),nStartVertexLocation,nVertexCount);
}

void GLRenderDevice::DrawIndexed( PrimitiveType::Type ePrimitiveType,uint nIndexCount,uint nStartIndexLocation )
{
	if(m_nVertexBufferCount==0 || m_ppVertexBuffers==nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the vertex buffer is not set, please set the vertex buffer before you call draw.");
		return;
	}

	if(m_pIndexBuffer == nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the index buffer is not set, set the index buffer before you call DrawIndexed.")
		return;
	}

	if(m_pAttributeLayout == nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the input layout object is not set.");
		return;
	}
	
	GLRenderBuffer *pBuffer = nullptr;
	GLenum eGLValueType = 0;
	GLsizei stride =0;

	for(uint i=0; i<m_pAttributeLayout->GetLayoutCount(); ++i)
	{
		pBuffer = m_ppVertexBuffers[m_pAttributeLayout->GetDesc(i).attributeSlot];
		eGLValueType = GetGLValueType(this,m_pAttributeLayout->GetDesc(i).varType);
		stride = m_pAttributeLayout->GetDesc(i).aligenedByteOffset;

		glBindBuffer(GL_ARRAY_BUFFER,pBuffer->GetGLBufID()); 
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,m_pAttributeLayout->GetDescElementCount(i),eGLValueType,false,m_pAttributeLayout->GetAttributeVertexSize(),(void *)stride);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_pIndexBuffer->GetGLBufID());
	glDrawElements(MapPrimitiveTypeToGLType(ePrimitiveType),nIndexCount, m_eIndexType,(void*)nStartIndexLocation);
}

void GLRenderDevice::SetVertexBuffers( IRenderBuffer **ppBuffers,uint nBufferCount)
{
	CH_ASSERT(ppBuffers!=nullptr);

	if(m_pAttributeLayout == nullptr)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: SetVertexBuffers the input layout object is not set.");
		return;
	}

	for(uint i=0; i<m_nVertexBufferCount; ++i)
	{
		if(m_ppVertexBuffers[i])
		{
			m_ppVertexBuffers[i]->DeRef();
			m_ppVertexBuffers[i] = nullptr;
		}
	}
	
	CH_ASSERT(nBufferCount <= INPUT_VERTEX_BUF_COUNT);
	
	for(uint i=0; i<nBufferCount; ++i)
	{
		if(ppBuffers[i]==nullptr)
		{
			CH_RENDER_TRACE_ERROR(this,"[rd] error: the input parm ppBuffer has null member, when call SetVertexBuffers, please check.");
			return;
		}

		m_ppVertexBuffers[i] = (GLRenderBuffer*)ppBuffers[i];
		m_ppVertexBuffers[i]->AddRef();
	}
	m_nVertexBufferCount = nBufferCount;

}

void GLRenderDevice::SetIndexBuffer( IRenderBuffer *pIndexBuffer,RVariableType::Type eIndexType,uint offset )
{
	CH_ASSERT(pIndexBuffer!=nullptr,"[rd] error: input parameter pIndexBuffer is null.");

	if(!(eIndexType==RVariableType::UNSIGNED_BYTE || 
			eIndexType == RVariableType::UNSIGNED_SHORT || eIndexType == RVariableType::UNSIGNED_INT) )
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: index type must be UNSIGNED_BYTE or UNSIGNED_SHORT or UNSIGNED_INT");
		return;
	}

	if(m_pIndexBuffer)
	{
		m_pIndexBuffer->DeRef();
		m_pIndexBuffer=nullptr;
	}

	m_pIndexBuffer = static_cast<GLRenderBuffer*>(pIndexBuffer);
	m_pIndexBuffer->AddRef();

	m_eIndexType = MapValueTypeToGLValueType(eIndexType);
	m_nIndexOffset = offset;
}

bool GLRenderDevice::SetVertexLayout( IInputLayout *pLayout)
{
	//validate the input layout object with current bind shader program
	if(nullptr == m_pShaderProgram)
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: before you set the vertex layout to the device, you should set shader program first.");
		return false;
	}

	if(nullptr == pLayout)
	{
		if( m_pAttributeLayout)
		{
			m_pAttributeLayout->DeRef();
			m_pAttributeLayout = nullptr;
		}
		return true;
	}

	GLInputLayout *pGLLayout = static_cast<GLInputLayout*>(pLayout);
#ifdef _DEBUG
	if(!pGLLayout->ValidateInputLayout(m_pShaderProgram))
	{
		CH_RENDER_TRACE_ERROR(this,"[rd] error: the input attribute layout not match the binded shader program's attributes, please check.");
		return false;
	}
#endif

	m_pAttributeLayout = pGLLayout;
	m_pAttributeLayout->AddRef();

	return true;
}

IRenderBuffer * GLRenderDevice::CreateBuffer( IRenderBuffer::Desc *pDesc, IRenderBuffer::InitData *pInitData )
{
	GLRenderBuffer *pBuffer = new GLRenderBuffer(this);
	if(!pBuffer->Init(pDesc,pInitData))
	{
		CH_SFDEL(pBuffer);
	}
	return pBuffer;
}

IInputLayout* GLRenderDevice::CreateInputLayout( IInputLayout::Desc *pLayoutArray,uint nLayoutCount,IShaderProgram *pProgram )
{
	GLInputLayout *pLayout = new GLInputLayout(this);

	if(!pLayout->Init(pLayoutArray,nLayoutCount))
	{
		CH_SFDEL(pLayout);
		return nullptr;
	}

	if(!pLayout->ValidateInputLayout((GLShaderProgram*)pProgram))
	{
		CH_SFDEL(pLayout);
	}

	return pLayout;
}

void GLRenderDevice::SetShaderProgram( IShaderProgram *pShaderProgram )
{
	if(m_pShaderProgram)
	{
		m_pShaderProgram->DeRef();
		m_pShaderProgram = nullptr;
	}

	if(pShaderProgram)
	{
		m_pShaderProgram = static_cast<GLShaderProgram*>(pShaderProgram);
		m_pShaderProgram->AddRef();
		glUseProgram(m_pShaderProgram->GetShaderProgramID());
		CH_GLFAILCHECK;
	}
}

ITexture2D* GLRenderDevice::CreateTexture2D( const ITexture2D::Desc* pDesc,const IRenderResource::InitData* pInitData )
{
	GLTexture2D *pTexture = new GLTexture2D(this);
	if(!pTexture->Init(pDesc,pInitData))
	{
		CH_SFDEL(pTexture);
	}
	return pTexture;
}

ITexture2D* GLRenderDevice::CreateTexture2D(const char *szFilePath)
{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib = nullptr;
	//pointer to the image data
	BYTE* bits = nullptr;
	//image width and height
	uint width=0, height=0;

	uint nBpp=0; 
	
	IFileStream* pFileStream = FileSystem::GetInstancePtr()->OpenFile(szFilePath,FILE_OPEN_READ);
	char* pFileDataBuffer=nullptr;
	uint nFileDataLength= pFileStream->GetFileSize();
	if(nFileDataLength==0)
	{
		CH_ERROR("[rd] error: the texture is empty");
	}
	pFileDataBuffer = new char[nFileDataLength];
	pFileStream->Read(pFileDataBuffer,nFileDataLength);
	CH_SFDEL(pFileStream);

	FIMEMORY* hmem = FreeImage_OpenMemory((BYTE*)pFileDataBuffer,nFileDataLength);
	

	//check the file signature and deduce its format
	fif = FreeImage_GetFileTypeFromMemory(hmem, nFileDataLength);
	if(fif == FIF_UNKNOWN)
	{
		CH_TRACE("[rd] error: can not load the texture. %s",szFilePath);
		CH_SFDELARR(pFileDataBuffer);
		return nullptr;
	}
	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_LoadFromMemory(fif,hmem,0);
		CH_SFDELARR(pFileDataBuffer);
	}
	//if the image failed to load, return failure
	if(!dib)
	{
		CH_TRACE("[rd] error: call FreeImage_Load failed.");
		return nullptr;
	}

	nBpp = FreeImage_GetBPP(dib);

	if(nBpp != 32)
	{
		FIBITMAP *t = FreeImage_ConvertTo32Bits(dib);
		FreeImage_Unload(dib);
		dib = t;
	}
	nBpp = FreeImage_GetBPP(dib);
	

	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if( (width == 0) || (height == 0))
	{
		CH_TRACE("[rd] error: not a vaildate texture.");
		FreeImage_Unload(dib);
		return nullptr;
	}

	uint surfacePitch = FreeImage_GetPitch(dib);
	uint nBitmapBytes = width * height * nBpp/8;
	bits = new BYTE[nBitmapBytes];	
	FreeImage_ConvertToRawBits(bits,dib,surfacePitch,nBpp,0xff000000,0x00ff0000,0x0000ff00,false);
	//memcpy(bits,FreeImage_GetBits(dib),nBitmapBytes);
	for(uint i=0;i<nBitmapBytes; i+=4)
	{
		swap(bits[i],bits[i+2]);
	}

	ITexture2D::Desc tDesc;
	tDesc.arraySize =1 ;
	tDesc.bindFlags = IRenderResource::SHADER_RESOURCE;
	tDesc.format = nBpp==24?ColorFormat::RGB:ColorFormat::RGBA;
	tDesc.width = width;
	tDesc.height = height;
	tDesc.mipLevels =0;
	tDesc.usage = IRenderResource::IMMUTABLE;

	IRenderResource::InitData initData;
	initData.pSysMem = bits;

	ITexture2D *pTexture = CreateTexture2D(&tDesc,&initData);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);
	CH_SFDELARR(bits);
	return pTexture;
}

void GLRenderDevice::AfterDeviceCreated()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	GLint nMaxTextureCount = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,&nMaxTextureCount);
	CH_TRACE("[rd] gl support %d texture unit.",nMaxTextureCount);
	GLint nMaxAttributeCount=0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nMaxAttributeCount);
	CH_TRACE("[rd] gl support %d attributes",nMaxAttributeCount);
}



NS_CH_END