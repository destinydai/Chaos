

#pragma once


NS_CH_BEG

class NativeWindow_android : public Window
{
public:
	NativeWindow_android(ANativeWindow* pWnd);
	virtual ~NativeWindow_android(void);

public:
	ANativeWindow* GetNativeWindow() { return m_pNWnd; }

protected:
	ANativeWindow* m_pNWnd;
};

NS_CH_END