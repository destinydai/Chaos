#include "stdafx.h"


NS_CH_BEG


Win32Window::Win32Window():
	m_hWnd(0),
		m_hdc(0),
		m_hInstance(0),
		m_pOnIdle(0),
		m_pUserData(0)
{

}

Win32Window::~Win32Window()
{

}

LRESULT WINAPI Win32Window::WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	Win32Window *pWindow =(Win32Window*) (LONG_PTR) GetWindowLongPtr ( hWnd, GWL_USERDATA );
	if(pWindow)
	{
		return pWindow->HandleMessage(uMsg,wParam,lParam);
	}

	return DefWindowProc (hWnd, uMsg, wParam, lParam); 
	
}

bool Win32Window::Create(const wchar *szWinTitle, uint nWidth, uint nHeight )
{
	WNDCLASS wndclass = {0}; 
	DWORD    wStyle   = 0;
	RECT     windowRect;
	m_hInstance = GetModuleHandle(NULL);


	wndclass.style         = CS_OWNDC;
	wndclass.lpfnWndProc   = (WNDPROC)WinProc; 
	wndclass.hInstance     = m_hInstance; 
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
	wndclass.lpszClassName = GetWinRegistClassName();

	if (!RegisterClass (&wndclass) ) 
		return FALSE; 

	wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

	// Adjust the window rectangle so that the client area has
	// the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = nWidth;
	windowRect.bottom = nHeight;

	AdjustWindowRect ( &windowRect, wStyle, FALSE );

	m_hWnd = CreateWindow(
		GetWinRegistClassName(),
		szWinTitle,
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL);

	if(m_hWnd == NULL)
	{
		return false;
	}

	SetCursor(LoadCursor(NULL, IDC_ARROW));

	m_hdc = GetDC(m_hWnd);
	SetWindowLongPtr (  m_hWnd, GWL_USERDATA, (LONG) (LONG_PTR) this );

	ShowWindow(m_hWnd,SW_SHOW);

	m_nWidth = nWidth;
	m_nHeight = nHeight;

	return true;
}

LRESULT Win32Window::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT  lRet = 1; 
	switch (uMsg) 
	{ 
	case WM_CREATE:
		break;

	case WM_PAINT:
		{
			//PAINTSTRUCT ps;
			//m_hdc = BeginPaint( m_hWnd, &ps );

			//EndPaint( m_hWnd, &ps );
			ValidateRect( m_hWnd, NULL );
		}
		break;
	case WM_CHAR:
		{
			POINT      point;

			GetCursorPos( &point );
			this->OnCharMessage((unsigned char)wParam,(int)point.x,(int)point.y);
		}
		break;
	case WM_DESTROY:
		if(m_pOnDestroyWindow)
		{
			m_pOnDestroyWindow(this);
		}
		PostQuitMessage(0);             
		break; 
	case WM_SIZE:
		if(m_pOnSizeChanged)
		{
			m_pOnSizeChanged(this,LOWORD(lParam),HIWORD(lParam));
		}
		break;
	default: 
		lRet = DefWindowProc (m_hWnd, uMsg, wParam, lParam); 
		break; 
	} 
	return lRet; 
}

void Win32Window::Run()
{
	MSG msg = { 0 };
	int done = 0;
	DWORD lastTime = GetTickCount();

	while (!done)
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0 )
		{
			if (msg.message==WM_QUIT)
			{
				done=1; 
			}
			else
			{
				TranslateMessage(&msg); 
				DispatchMessage(&msg); 
			}
		}
		else
		{
			if (m_pOnIdle)
				m_pOnIdle(m_pUserData);
		}
	}
}

void Win32Window::Close( void )
{
	SendMessage(m_hWnd,WM_QUIT,0,0);
}


NS_CH_END