#pragma once

NS_CH_BEG

class Win32Window : public Window
{
public:
	Win32Window();
	virtual ~Win32Window();

	typedef void (*pfn_OnIdle)(void *pUserParm);

public: 

	inline void SetOnIdleEvent(pfn_OnIdle pfn, void *pUserData) { m_pOnIdle=pfn; m_pUserData = pUserData; }

	inline HWND GetWind() { return m_hWnd; }

	bool Create(const wchar *szWinTitle,uint nWidth, uint nHeight);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual const wchar *GetWinRegistClassName() const { return L"ChaosWin32Window"; }

	virtual void OnCharMessage(unsigned char key,int x,int y) {}

	virtual void OnPaint() {}

	virtual void Run();

	void Close(void);
protected:
	static LRESULT WINAPI WinProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

public:
	HWND m_hWnd;
	HDC m_hdc;
	HINSTANCE m_hInstance;
	pfn_OnIdle m_pOnIdle;
	void *m_pUserData;

};

NS_CH_END