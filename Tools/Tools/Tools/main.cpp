

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <d3d10.h>
#include <D3DX10.h>

HWND											g_hWnd = NULL;
HINSTANCE									g_hInst = NULL;
D3D10_DRIVER_TYPE                   g_driverType = D3D10_DRIVER_TYPE_NULL;
ID3D10Device*								 g_pd3dDevice = NULL;
IDXGISwapChain*							  g_pSwapChain = NULL;
ID3D10Effect*								 g_pEffect = NULL;


HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice(const char *szEffectPath, const char* szEffectVersion);
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

#define LOG_TRACE(...) printf(__VA_ARGS__);printf("\n");

int main(int argc, const char* argv[])
{
	if(argc<2)
	{
		LOG_TRACE("the valid input is: EffectFilePath EffectVersion");
		LOG_TRACE("valid version is 'fx_4_0' or 'fx_3_0'");
		return 1;
	}
	const char *szDefaultVersion = "fx_4_0";
	const char* szEffectFile = argv[1];
	const char* szEffectVerison = szDefaultVersion;
	if(argc==3)
	{
		szEffectVerison = argv[2];
	}

	if(FAILED(InitWindow(0,SW_HIDE)))
	{
		LOG_TRACE("create window failed.");
		return 1;
	}

	if(FAILED(InitDevice(szEffectFile,szEffectVerison)))
	{
		return 1;
	}

	LOG_TRACE("succeed");

	return 0;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"HLSLEffectErrorChecker";
	wcex.hIconSm = 0;
	if( !RegisterClassEx( &wcex ) )
		return E_FAIL;

	// Create window
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	g_hWnd = CreateWindow( L"HLSLEffectErrorChecker", L"HLSL Effect Error Checker", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !g_hWnd )
		return E_FAIL;

	ShowWindow( g_hWnd, nCmdShow );

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice(const char *szEffectPath, const char* szEffectVersion)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect( g_hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	D3D10_DRIVER_TYPE driverTypes[] =
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = sizeof( driverTypes ) / sizeof( driverTypes[0] );

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ )
	{
		g_driverType = driverTypes[driverTypeIndex];
		hr = D3D10CreateDeviceAndSwapChain( NULL, g_driverType, NULL, createDeviceFlags,
			D3D10_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice );
		if( SUCCEEDED( hr ) )
			break;
	}
	if( FAILED( hr ) )
		return hr;

	// Create the effect
	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3D10_SHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3D10_SHADER_DEBUG;
#endif
	ID3D10Blob* pErrBuf = nullptr;
	hr = D3DX10CreateEffectFromFileA(szEffectPath, NULL, NULL, szEffectVersion, dwShaderFlags, 0, g_pd3dDevice, NULL,
		NULL, &g_pEffect, &pErrBuf, NULL );
	if( FAILED( hr ) )
	{
		char* szErrorBuf = nullptr;
		if(pErrBuf!=nullptr)
		{
			szErrorBuf = new char[pErrBuf->GetBufferSize()+1];
			szErrorBuf[pErrBuf->GetBufferSize()]=0;
			memcpy(szErrorBuf,pErrBuf->GetBufferPointer(),pErrBuf->GetBufferSize());
		}

		//remove file path 
		const char* itr = strstr(szErrorBuf,szEffectPath);
		if(itr != nullptr)
		{
			int nLen = strlen(szEffectPath);
			const char *pTail = itr+nLen;
			for(; pTail != itr; --pTail)
			{
				if(*pTail == '/' || *pTail=='\\')
				{
					++pTail;
					break;
				}
			}
			LOG_TRACE(pTail);
		}
		else
		{
			LOG_TRACE(szErrorBuf);
		}
		return hr;
	}

	return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
	if( g_pd3dDevice ) g_pd3dDevice->ClearState();

	if( g_pEffect ) g_pEffect->Release();

	if( g_pd3dDevice ) g_pd3dDevice->Release();
}


LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return 0;
}