#include "stdafx.h"


NS_CH_BEG

NativeWindow_android::NativeWindow_android( NativeActivity_android* pActivity):
	m_pActivity(pActivity)
{
	
}

NativeWindow_android::~NativeWindow_android( void )
{

}

void NativeWindow_android::OnNativeWindowCreated( ANativeActivity* activity, ANativeWindow* pWnd )
{
	CH_TRACE("[pl] info: Android native window create succeed");
	CriticalSection::ScopeLock locker(m_msgLock);

	if(m_pWnd != nullptr)
	{

	}
}

NS_CH_END