#pragma once


NS_CH_BEG

class Window
{
public:
	typedef void (*Pfn_OnSizeChanged)(Window* pSender, uint nWidth,uint nHeight);
	typedef void (*Pfn_OnFocused)(Window* pSender);
	typedef void (*Pfn_OnLostFocus)(Window* pSender);
	typedef void (*Pfn_OnDestroyWindow)(Window* pSender);
protected:
	Window(void);
	virtual ~Window(void);
public:
	uint GetWidth() const { return m_nWidth; } 
	uint GetHeight() const { return m_nHeight; }

	void SetOnSizeChangedCallback(Pfn_OnSizeChanged pCallback){
		m_pOnSizeChanged = pCallback;
	}
	void SetOnFocusedCallback(Pfn_OnLostFocus pCallback){
		m_pOnFocused = pCallback;
	}
	void SetOnLostFocus(Pfn_OnLostFocus pCallback){
		m_pOnLostFocus = pCallback;
	}
	void SetOnDestroyWindow(Pfn_OnDestroyWindow pCallback){
		m_pOnDestroyWindow = pCallback;
	}

protected:
	uint m_nWidth;
	uint m_nHeight;
	
	Pfn_OnSizeChanged m_pOnSizeChanged;
	Pfn_OnFocused m_pOnFocused;
	Pfn_OnLostFocus m_pOnLostFocus;
	Pfn_OnDestroyWindow m_pOnDestroyWindow;
};

NS_CH_END