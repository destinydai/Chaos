#include "stdafx.h"

NS_CH_BEG

NativeActivity_android::NativeActivity_android( ANativeActivity* activity,void* savedState, size_t savedStateSize,Pfn_MainLoop pLoopMian):
	m_pActivity(activity),
	m_pSaveState(nullptr),
	m_nSaveStateSize(savedStateSize),
	m_pAssetManager(nullptr),
	m_pWindow(nullptr),
	m_msgread(0),
	m_msgwrite(0),
	m_pAppConfig(nullptr),
	m_pLooper(nullptr),
	m_notifyEvent(true,false),
	m_pMainLoopFunction(pLoopMian)
{
	if(savedState !=0)
	{
		m_pSaveState = new char[savedStateSize];
		memccpy(m_pSaveState,savedState,savedStateSize);
	}

	int msgpipe[2];
	if(pipe(msgpipe))
	{
		CH_ERROR("[pl] error: call pipe failed in Window_android::Window_android, could not create pipe:%s",strerror(errno));
		return;
	}

	m_msgread = msgpipe[0];
	m_msgwrite = msgpipe[1];

	if(!m_thread.startThread(NativeWindow_android::RunActivityThread,this))
	{
		CH_ERROR("[pl] error: Start Native Activity failed.");
		return;
	}

	//等待Activity Thread 开始工作
	if(!m_notifyEvent->waitSignal())
	{
		CH_ERROR("[pl] error: ThreadEvent wait failed.");
		return;
	}
}

NativeActivity_android::~NativeActivity_android( void )
{
	CH_SFDEL(m_pAssetManager);
	CH_SFDEL(m_pWindow);

	CH_SFDELARR((char*)m_pSaveState);
	m_nSaveStateSize=0;

	AConfiguration_delete(m_pAppConfig);
	m_pAppConfig=nullptr;
}

void NativeActivity_android::RunActivityThread(void* param)
{
	NativeActivity_android* pActivity = (NativeActivity_android*)param;
	pActivity->RunActive();
}

void NativeActivity_android::RunActive()
{
	m_pAppConfig = AConfiguration_new();
	AConfiguration_fromAssetManager(m_pAppConfig,m_pActivity->assetManager);

	PrintCurrentConfig();

	ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	if(-1==ALooper_addFd(looper,m_msgread,LOOPER_ID_MAIN,ALOOPER_EVENT_INPUT,nullptr,nullptr))
	{
		CH_ERROR("[pl] error: call ALooper_addFd api failed.");
		return;
	}
	//notify jvm thread looper has setuped
	m_notifyEvent.setEvent();

	if(m_pMainLoopFunction)
	{
		m_pMainLoopFunction();
	}
}


void NativeActivity_android::PrintCurrentConfig()
{
	char lang[2], country[2];
	AConfiguration_getLanguage(m_pAppConfig, lang);
	AConfiguration_getCountry(m_pAppConfig, country);

	CH_TRACE("[pl] Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
		"keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
		"modetype=%d modenight=%d",
		AConfiguration_getMcc(m_pAppConfig),
		AConfiguration_getMnc(m_pAppConfig),
		lang[0], lang[1], country[0], country[1],
		AConfiguration_getOrientation(m_pAppConfig),
		AConfiguration_getTouchscreen(m_pAppConfig),
		AConfiguration_getDensity(m_pAppConfig),
		AConfiguration_getKeyboard(m_pAppConfig),
		AConfiguration_getNavigation(m_pAppConfig),
		AConfiguration_getKeysHidden(m_pAppConfig),
		AConfiguration_getNavHidden(m_pAppConfig),
		AConfiguration_getSdkVersion(m_pAppConfig),
		AConfiguration_getScreenSize(m_pAppConfig),
		AConfiguration_getScreenLong(m_pAppConfig),
		AConfiguration_getUiModeType(m_pAppConfig),
		AConfiguration_getUiModeNight(m_pAppConfig));
}

void NativeActivity_android::StartActivityThread()
{
	//start message loop thread
	if(!m_thread.startThread(NativeActivity_android::RunActivityThread,this))
	{
		CH_ERROR("[pl] error: Start Native Activity failed.");
		return;
	}

	//等待Activity Thread message loop开始工作
	if(!m_notifyEvent->waitSignal())
	{
		CH_ERROR("[pl] error: ThreadEvent wait failed.");
		return;
	}
}

int8 NativeActivity_android::ReadCmd()
{
	int8_t cmd;
	if (read(m_msgread, &cmd,1) 
	{
		switch (cmd) {
		case APP_CMD_SAVE_STATE:
			FreeSavedState();
			break;
		}
		return cmd;
	} else {
		CH_ERROR("No data on command pipe!");
	}
	return -1;
}

void NativeActivity_android::FreeSavedState()
{
	CriticalSection::ScopeLock locker(m_lock);
	CH_SFDELARR((char*)m_pSaveState);
	m_nSaveStateSize = 0;
}


NS_CH_END