

#pragma once


NS_CH_BEG

class NativeWindow_android : public Window
{
public:
	NativeWindow_android(NativeActivity_android* pActivity);
	virtual ~NativeWindow_android(void);

public:
	static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* pWnd);

protected:
	NativeActivity_android* m_pActivity;
};

NS_CH_END