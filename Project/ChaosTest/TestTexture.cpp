

#include "stdafx.h"

using namespace Chaos;


#define CH_WIN_WIDTH 600
#define CH_WIN_HEIGHT 600


static IRenderDevice *m_pRender = nullptr;

static IRenderBuffer *m_pVertexBuffer;
static IRenderBuffer *m_pIndexBuffer;
static IShaderProgram *m_pShaderProgram;
static IVertexShader *m_pVertexShader;
static IPixelShader *m_pPixelShader;
static IInputLayout *m_pLayoutObject;
static ITexture2D *m_pTexture;
static IShaderVariable *m_pTextureVariable;

static bool m_bCanRun=true;

static inline IRenderDevice *GetDevice() { return m_pRender; }


void TestResMgr();

static bool Init(IRenderDevice *pRender)
{
	TestResMgr();

	m_pRender = pRender;
	char vShaderStr[] =  
		"attribute vec4 a_position;   \n"
		"attribute vec2 a_texCoord;   \n"
		"varying vec2 v_texCoord;     \n"
		"void main()                  \n"
		"{                            \n"
		"   gl_Position = a_position; \n"
		"   v_texCoord = a_texCoord;  \n"
		"}                            \n";

	char fShaderStr[] =  
		"precision mediump float;                            \n"
		"varying vec2 v_texCoord;                            \n"
		"uniform sampler2D s_texture;                        \n"
		"void main()                                         \n"
		"{                                                   \n"
		"  gl_FragColor = texture2D( s_texture, v_texCoord );\n"
		"}                                                   \n";
	
	CH_TRACE("[game] Begin create Vertex Shader.");
	m_pVertexShader = GetDevice()->CreateVertexShader(vShaderStr,sizeof(vShaderStr));
	if(m_pVertexShader==0)
		return false;
	CH_TRACE("[game] Vertex Shader create succeed.");
	
	m_pPixelShader = GetDevice()->CreatePixelShader(fShaderStr,sizeof(fShaderStr));
	if(m_pPixelShader==0)
		return false;
	CH_TRACE("[game] Pixel Shader create succeed.");
	
	m_pShaderProgram = GetDevice()->CreateShaderProgram(m_pVertexShader,m_pPixelShader);
	if(m_pShaderProgram==0)
		return 0;	
	
	CH_TRACE("%s",m_pShaderProgram->ToString().c_str());
	
	float vVertices[] = { -0.5f,  0.5f, 0.0f,1.0f,  // Position 0
		0.0f,  1.0f,        // TexCoord 0 
		-0.5f, -0.5f, 0.0f,1.0f,  // Position 1
		0.0f,  0.0f,        // TexCoord 1
		0.5f, -0.5f, 0.0f,1.0f,  // Position 2
		1.0f,  0,        // TexCoord 2
		0.5f,  0.5f, 0.0f,  1.0f, // Position 3
		1.0f,  1.0f         // TexCoord 3
	};

	IRenderBuffer::Desc bufDesc;
	bufDesc.usage = IRenderResource::IMMUTABLE;
	bufDesc.bindFlag = IRenderResource::VERTEX_BUFFER;
	bufDesc.bytes = sizeof(vVertices);
	IRenderResource::InitData initData(vVertices,0,0);
	m_pVertexBuffer = GetDevice()->CreateBuffer(&bufDesc,&initData);
	if(m_pVertexBuffer==0)
		return false;
	IInputLayout::Desc layoutDesc[2];
	layoutDesc[0].attributeSlot = 0;
	layoutDesc[0].varType = RVariableType::VEC4;
	layoutDesc[0].vertexType = VertexType::POSITION;
	layoutDesc[0].aligenedByteOffset = 0;

	layoutDesc[1].attributeSlot = 0;
	layoutDesc[1].varType = RVariableType::VEC2;
	layoutDesc[1].vertexType = VertexType::TEXCOORD;
	layoutDesc[1].aligenedByteOffset = sizeof(Vector4);

	m_pLayoutObject = GetDevice()->CreateInputLayout(layoutDesc,2,m_pShaderProgram);
	if(m_pLayoutObject == nullptr)
		return false;

	uint16 indices[] = { 0, 1, 2, 0, 2, 3 };
	bufDesc.bytes = sizeof(indices);
	initData.pSysMem = indices;

	m_pIndexBuffer = GetDevice()->CreateBuffer(&bufDesc,&initData);

	ITexture2D::Desc texDesc;
	texDesc.arraySize=1;
	texDesc.bindFlags=IRenderResource::SHADER_RESOURCE;
	texDesc.format = ColorFormat::RGB;
	texDesc.height = 2;
	texDesc.width = 2;
	texDesc.mipLevels=0;
	texDesc.usage = IRenderResource::IMMUTABLE;
	
	unsigned char pixels[4 * 3] =
	{  
		255,   0,   0, // Red
		0,  255,   0, // Green
		0,   0, 255, // Blue
		255, 255,   0  // Yellow
	};

	IRenderResource::InitData texInitData;
	texInitData.pSysMem = pixels;
	
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	m_pTexture = GetDevice()->CreateTexture2D("Data/d2.bmp");
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	//m_pTexture = GetDevice()->CreateTexture2D(&texDesc,&texInitData);
	m_pTexture = GetDevice()->CreateTexture2D("Data/d2.bmp");
#else
	CH_ERROR("not implement yet");
#endif
	
	if(m_pTexture==0)
	{
		CH_TRACE("[game] load texture failed.");
		return false;
	}
	GetDevice()->SetClearColor(Color3(0,0,0));
	GetDevice()->SetClearDepth(1.0f);
	GetDevice()->SetClearStencil(0);

	GetDevice()->SetViewport(0,0,CH_WIN_WIDTH,CH_WIN_HEIGHT);
	
	m_pTextureVariable = m_pShaderProgram->GetVariableByName("s_texture");
	if(m_pTextureVariable == 0)
		return false;
	CH_TRACE("[game] init complete");
	return true;
}

static void Draw()
{
	float r=(rand()%256) /256.0f;
	float g=(rand()%256) /256.0f;
	float b=(rand()%256) /256.0f;
	GetDevice()->SetClearColor(Color3(r,g,b));

	GetDevice()->ClearBuffer(true,true,true);

	GetDevice()->SetShaderProgram(m_pShaderProgram);
	GetDevice()->SetVertexLayout(m_pLayoutObject);
	GetDevice()->SetIndexBuffer(m_pIndexBuffer,RVariableType::UNSIGNED_SHORT,0);
	GetDevice()->SetVertexBuffers(&m_pVertexBuffer,1);
	m_pTextureVariable->SetTexture2D(0,m_pTexture);
	GetDevice()->DrawIndexed(PrimitiveType::TRIANGLE_LIST,6,0);

	GetDevice()->SwapBuffer();
}

static void Update(void *pUserData)
{
	Draw();
}


static void ShutDown()
{
	if(m_pTexture)
		m_pTexture->DeRef();

	if(m_pVertexShader)
		m_pVertexShader->DeRef();

	if(m_pPixelShader)
		m_pPixelShader->DeRef();

	if(m_pShaderProgram)
		m_pShaderProgram->DeRef();

	if(m_pVertexBuffer)
		m_pVertexBuffer->DeRef();

	if(m_pIndexBuffer)
		m_pIndexBuffer->DeRef();
}

void PrintStringArray(const StringArray& arr)
{
	for(int i=0; i<arr.size(); ++i)
	{
		CH_TRACE("%s",arr[i].c_str());
	}
}

int main(int argc, const char* argv[])
{
	Application::GetInstancePtr()->SetOnIdleProc(Update,0);
	Application::GetInstancePtr()->SetOnRenderDeviceCreated(Init);

	if(!Application::GetInstancePtr()->Create(CH_WIN_WIDTH,CH_WIN_HEIGHT))
	{
		CH_TRACE("create application failed.");
		return 1;
	}

	Application::GetInstancePtr()->Run();

	ShutDown();

	return 0;
}



void TestResMgr()
{
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	IFileDirectory* pDirInclude = FileSystem::GetInstancePtr()->OpenDirectory("Include");
	IFileDirectory* pDirSource = FileSystem::GetInstancePtr()->OpenDirectory("Source/");
	IFileDirectory* pDirData = FileSystem::GetInstancePtr()->OpenDirectory("./Data/");

	StringArray arrIncludes,arrSource,arrDatas;
	pDirInclude->ListAllFiles(arrIncludes);
	pDirSource->ListAllFiles(arrSource);
	pDirData->ListAllFiles(arrDatas);
	PrintStringArray(arrIncludes);
	PrintStringArray(arrSource);
	PrintStringArray(arrDatas);

	StringArray inFolder,srcFolder;
	pDirInclude->ListAllDirectory(inFolder);
	pDirSource->ListAllDirectory(srcFolder);
	PrintStringArray(inFolder);
	PrintStringArray(srcFolder);
#endif
	CH_TRACE("[game] begin list root files");
	IFileDirectory* pRoot = FileSystem::GetInstancePtr()->OpenDirectory("Data");
	StringArray dataFiles;
	pRoot->ListFiles(dataFiles);
	PrintStringArray(dataFiles);
}