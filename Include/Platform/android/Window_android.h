

#pragma once


NS_CH_BEG

class Window_android : public Window
{
public:
	Window_android(ANativeActivity* activity,void* savedState, size_t savedStateSize);
	virtual ~Window_android(void);

	typedef void (*Pfn_OnActivityDestroy)(ANativeActivity* activity);
	typedef void (*Pfn_OnStartActivity)(ANativeActivity* activity);
	typedef void (*Pfn_OnResumeActivity)(ANativeActivity* activity);
	typedef void (*Pfn_OnPauseActivity)(ANativeActivity* activity);
	typedef void (*Pfn_OnStopActivity)(ANativeActivity* activity);
	typedef void (*Pfn_OnSaveInstanceState)(ANativeActivity* activity);
	typedef void (*Pfn_OnConfigurationChanged)(ANativeActivity* activity);
	typedef void (*Pfn_OnLowMemory)(ANativeActivity* activity);

public:
	static void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* pWnd);

	static void RunActivityThread(void* pData);

private:
	void RunActivity();

	void PrintCurrentConfig();
protected:
	
	ANativeWindow* m_pWnd; 
	

	ANativeActivity* m_pActivity;
	void *m_pSaveState;
	size_t m_nSaveStateSize;
	int m_msgread;
	int m_msgwrite;
	AConfiguration* m_pAppConfig;
	CriticalSection m_msgLock;
	ThreadEvent* m_notifyEvent;
	Thread m_thread;
};

NS_CH_END