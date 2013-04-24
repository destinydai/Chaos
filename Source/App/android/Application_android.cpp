#include "stdafx.h"

#if CH_PLATFORM==CH_PLATFORM_ANDROID

#include "App/android/Application_android.h"
#include "Platform/android/NativeWindow_android.h"


extern int main(int argc, const char* argv[]);

NS_CH_BEG

Application_android::Application_android( void ):
	m_pActivity(nullptr),
	m_pOnIdle(nullptr),
	m_pUserParm(nullptr),
	m_pSensorManager(nullptr),
	m_pAccelerometerSensor(nullptr),
	m_pSensorEventQueue(nullptr),
	m_bExit(false),
	m_pSaveState(nullptr),
	m_nSaveStateSize(0),
	m_msgread(0),
	m_msgwrite(0),
	m_pAppConfig(nullptr),
	m_pLooper(nullptr),
	m_bRunning(false),
	m_activityState(0),
	m_pWindow(nullptr),
	m_pPendingWindow(nullptr),
	m_OnRenderDeviceCreated(nullptr)
{

}


void Application_android::ReleaseMember()
{
	NativeWindow_android* pWnd = GetNativeWindow();
	CH_SFDEL(pWnd);
	m_pWindows = nullptr;

	m_pActivity = nullptr;
	m_pOnIdle = nullptr;
	m_pUserParm = nullptr;
	m_pSensorManager=nullptr;
	m_pAccelerometerSensor=nullptr;
	m_pSensorEventQueue=nullptr;
	m_bExit=false;
	m_pSaveState=nullptr;
	m_nSaveStateSize=0;
	m_msgread=0;
	m_msgwrite=0;
	m_pAppConfig=nullptr;
	m_pLooper=nullptr;
	m_bRunning=false;
	m_activityState=0;
	m_pWindow=nullptr;
	m_pPendingWindow=nullptr;
	m_OnRenderDeviceCreated=nullptr;

}

Application_android::~Application_android( void )
{
	
}


void Application_android::PrintCurrentConfig()
{
	char lang[2], country[2];
	AConfiguration_getLanguage(m_pAppConfig, lang);
	AConfiguration_getCountry(m_pAppConfig, country);

	CH_TRACE("[app] Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
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


bool Application_android::Create( uint nWidth,uint nHeight )
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	return true;
}

void Application_android::SetOnIdleProc( pfn_OnIdle onIdle,void *pUserParm )
{
	m_pOnIdle = onIdle;
	m_pUserParm = pUserParm;
}

void Application_android::Close()
{

}


void Application_android::ProcessEvent( ASensorEvent* event )
{
	CH_TRACE("[app] accelerometer: x=%f y=%f z=%f",event->acceleration.x, event->acceleration.y,event->acceleration.z);
}

void Application_android::ProcessSysEvent( void )
{
	int8 cmd =AppReadCmd();
	PreProcessSysCmd(cmd);
	//调用相应的注册回调

	PostProcessSysCmd(cmd);
}

void Application_android::PreProcessSysCmd(int8 cmd)
{
	switch(cmd)
	{
	case APP_CMD_INIT_WINDOW:
		CH_TRACE("[app] APP_CMD_INIT_WINDOW\n");
		pthread_mutex_lock(&this->mutex);
		this->m_pWindow = this->m_pPendingWindow;

		m_pRenderDevice = CreateRender(this->m_pWindow);
		if(m_pRenderDevice==nullptr)
		{
			CH_ERROR("[app] error: create render device failed.");
		}
		else
		{
			CH_TRACE("[app] create render device succeed.");
			m_OnRenderDeviceCreated(m_pRenderDevice);
		}
		pthread_cond_broadcast(&this->cond);
		pthread_mutex_unlock(&this->mutex);
		break;

	case APP_CMD_TERM_WINDOW:
		CH_TRACE("APP_CMD_TERM_WINDOW\n");
		pthread_cond_broadcast(&this->cond);
		break;
	case APP_CMD_RESUME:
	case APP_CMD_START:
	case APP_CMD_PAUSE:
	case APP_CMD_STOP:
		CH_TRACE("[app] activityState=%d\n", cmd);
		pthread_mutex_lock(&mutex);
		m_activityState = cmd;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex);
		break;
	}
}

void Application_android::PostProcessSysCmd(int8 cmd)
{

}


void Application_android::FreeSavedState()
{

}

void Application_android::JvmOnDestroy( ANativeActivity* activity )
{
	CH_TRACE("[app] Activity Destroy: %p\n", activity);

}


void Application_android::SetAppActivityState( int8_t cmd )
{
	pthread_mutex_lock(&mutex);
	AppWriteCmd(cmd);
	while (m_activityState != cmd) {
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock(&mutex);
}


//通知逻辑线程，Activity开始运行了
void Application_android::JvmOnStart( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] Activity Start: %p", activity);
	pApp->SetAppActivityState(APP_CMD_START);
}

void Application_android::JvmOnResume( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] Resume: %p", activity);
	pApp->SetAppActivityState(APP_CMD_RESUME);
}

void* Application_android::JvmOnSaveInstanceState( ANativeActivity* activity, size_t* outLen )
{
	Application_android* pApp =(Application_android*)activity->instance;
	void* savedState = nullptr;

	 CH_TRACE("[app] SaveInstanceState: %p", activity);
	 pthread_mutex_lock(&pApp->mutex);
	 pApp->m_bStateSaved = 0;
	 pApp->AppWriteCmd(APP_CMD_SAVE_STATE);
	 while (!pApp->m_bStateSaved) {
		 pthread_cond_wait(&pApp->cond, &pApp->mutex);
	 }

	 if(pApp->m_pSaveState != nullptr)
	 {
		 savedState = pApp->m_pSaveState;
		 *outLen = pApp->m_nSaveStateSize;
		 pApp->m_pSaveState = nullptr;
		 pApp->m_nSaveStateSize =0;
	 }

	 pthread_mutex_unlock(&pApp->mutex);
	 return savedState;
}

void Application_android::JvmOnPause( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] Pause: %p", activity);
	pApp->SetAppActivityState( APP_CMD_PAUSE);
}

void Application_android::JvmOnStop( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] Stop: %p", activity);
	pApp->SetAppActivityState( APP_CMD_STOP);
}

void Application_android::JvmOnConfigurationChanged( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] ConfigurationChanged: %p", activity);
	pApp->AppWriteCmd(APP_CMD_CONFIG_CHANGED);
}

void Application_android::JvmOnLowMemory( ANativeActivity* activity )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] LowMemory: %p", activity);
	pApp->AppWriteCmd(APP_CMD_LOW_MEMORY);
}

void Application_android::JvmOnWindowFocusChanged( ANativeActivity* activity, int focused )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] WindowFocusChanged: %p", activity);
	pApp->AppWriteCmd( focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

void Application_android::JvmOnNativeWindowCreated( ANativeActivity* activity, ANativeWindow* window )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] NativeWindowCreated: %p -- %p", activity,window);
	pApp->AppSetWindow(window);
}

void Application_android::JvmOnNativeWindowDestroyed( ANativeActivity* activity, ANativeWindow* window )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] NativeWindowDestroyed: %p -- %p", activity,window);
	pApp->AppSetWindow(window);
}

void Application_android::JvmOnInputQueueCreated( ANativeActivity* activity, AInputQueue* queue )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] InputQueueCreated: %p -- %p", activity,queue);
	pApp->OnInputQueueCreated(queue);
}

void Application_android::JvmOnInputQueueDestroyed( ANativeActivity* activity, AInputQueue* queue )
{
	Application_android* pApp =(Application_android*)activity->instance;
	CH_TRACE("[app] JvmOnInputQueueDestroyed: %p -- %p", activity,queue);
	pApp->OnInputQueueDestroyed(queue);
}

void Application_android::AppWriteCmd( int8_t cmd)
{
	 if (write(m_msgwrite, &cmd, sizeof(cmd)) != sizeof(cmd)) 
	{
		CH_ERROR("Failure writing android_app cmd \n");
	}
}

int8_t Application_android::AppReadCmd()
{
	int8_t cmd;
	 if (read(m_msgread, &cmd, sizeof(cmd)) == sizeof(cmd)) {
		switch (cmd) {
		case APP_CMD_SAVE_STATE:
			FreeSavedState();
			break;
		}
		return cmd;
	} else {
		CH_ERROR("[app] error:No data on command pipe!");
	}
	return -1;
}


void Application_android::Run( void )
{
	while(1)
	{
		int ident;
		int events;
		void* pMsg=nullptr;

		while((ident=ALooper_pollAll(0,nullptr,&events,&pMsg))>=0)
		{
			this->ProcessSysEvent();

			if(ident == LOOPER_ID_USER)
			{
				if(m_pAccelerometerSensor != nullptr)
				{
					ASensorEvent event;
					while(ASensorEventQueue_getEvents(m_pSensorEventQueue,&event,1)>0){
						ProcessEvent(&event);
					}
				}
			}

			if(m_bExit==true)
			{
				return;
			}

		}//all message in queue has been processed

		if(m_pOnIdle && m_pRenderDevice)
		{
			m_pOnIdle(m_pUserParm);
		}
	}
}

void* Application_android::RunActivityThread( void* param )
{
	Application_android* pApp = (Application_android*)param;
	pApp->RunActive();
}

void Application_android::RunActive()
{
	m_pAppConfig = AConfiguration_new();
	AConfiguration_fromAssetManager(m_pAppConfig,m_pActivity->assetManager);

	PrintCurrentConfig();

	m_pLooper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	if(-1==ALooper_addFd(m_pLooper,m_msgread,LOOPER_ID_MAIN,ALOOPER_EVENT_INPUT,nullptr,nullptr))
	{
		CH_ERROR("[pl] error: call ALooper_addFd api failed.");
		return;
	}

	CH_TRACE("[app] notify jvm thread looper has setuped");
	pthread_mutex_lock(&mutex);
	m_bRunning = true;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);

	m_pSensorManager = ASensorManager_getInstance();
	m_pAccelerometerSensor = ASensorManager_getDefaultSensor(m_pSensorManager,ASENSOR_TYPE_ACCELEROMETER);
	m_pSensorEventQueue = ASensorManager_createEventQueue(m_pSensorManager,
		m_pLooper, LOOPER_ID_USER, NULL, NULL);

	const char* szParms[1] = {"/"};
	main(1,szParms);
}

void Application_android::AppInit(ANativeActivity* activity,void* savedState, size_t savedStateSize)
{
	ReleaseMember();

	CH_TRACE("[app] NativeActivity create complete %p", activity);
	activity->callbacks->onDestroy = JvmOnDestroy;
	activity->callbacks->onStart = JvmOnStart;
	activity->callbacks->onResume = JvmOnResume;
	activity->callbacks->onSaveInstanceState = JvmOnSaveInstanceState;
	activity->callbacks->onPause = JvmOnPause;
	activity->callbacks->onStop = JvmOnStop;
	activity->callbacks->onConfigurationChanged = JvmOnConfigurationChanged;
	activity->callbacks->onLowMemory = JvmOnLowMemory;
	activity->callbacks->onWindowFocusChanged = JvmOnWindowFocusChanged; 
	activity->callbacks->onNativeWindowCreated = JvmOnNativeWindowCreated;
	activity->callbacks->onNativeWindowDestroyed = JvmOnNativeWindowDestroyed;
	activity->callbacks->onInputQueueCreated = JvmOnInputQueueCreated;
	activity->callbacks->onInputQueueDestroyed = JvmOnInputQueueDestroyed;
	activity->instance = this;
	m_pActivity = activity;
	FileSystem::GetInstancePtr()->SetAPIContex(activity->assetManager);
	int r = pthread_mutex_init(&mutex, NULL);
	r= pthread_cond_init(&cond, NULL);

	if(r!=0)
	{
		CH_ERROR("[app] error: init mutex or cond failed.");
	}

	if(savedState!=nullptr)
	{
		m_pSaveState = new char[savedStateSize];
		memcpy(m_pSaveState,savedState,savedStateSize);
		m_nSaveStateSize=savedStateSize;
	}

	int msgpipe[2];
	if(pipe(msgpipe))
	{
		CH_ERROR("[pl] error: call pipe failed in Application_android::AppInit, could not create pipe ");
		return;
	}

	m_msgread = msgpipe[0];
	m_msgwrite = msgpipe[1];

	pthread_attr_t attr; 
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	r =pthread_create(&m_thread, &attr, Application_android::RunActivityThread, this);
	if(r!=0)
	{
		CH_ERROR("[app] error: pthread_create failed. ");
		return;
	}

	//等待Activity Thread 开始工作
	CH_TRACE("[app] wait main msg loop thread to start. ");
	pthread_mutex_lock(&mutex);
	while (!this->m_bRunning) {
		pthread_cond_wait(&cond, &mutex);
	}
	pthread_mutex_unlock( &mutex);
}

void Application_android::AppSetWindow(ANativeWindow* window)
{
	pthread_mutex_lock(&mutex);
	if (m_pPendingWindow != NULL) {
		AppWriteCmd(APP_CMD_TERM_WINDOW);
	}
	m_pPendingWindow = new NativeWindow_android(window);
	if (window != NULL) {
		AppWriteCmd(APP_CMD_INIT_WINDOW);
	}
	while (this->m_pWindow != this->m_pPendingWindow) {
		pthread_cond_wait(&this->cond, &this->mutex);
	}
	pthread_mutex_unlock(&this->mutex);
	
}

void Application_android::OnInputQueueCreated( AInputQueue* queue )
{

}

void Application_android::OnInputQueueDestroyed( AInputQueue* queue )
{

}

IRenderDevice* Application_android::CreateRender(NativeWindow_android* pWnd)
{
	IRenderDevice* pDevice = CreateRenderDevice(pWnd->GetNativeWindow(),m_nWidth,m_nHeight,RenderDriverType::OPENGL,true);
	return pDevice;
}



NS_CH_END


void ANativeActivity_onCreate(ANativeActivity* activity,void* savedState, size_t savedStateSize) 
{
		using namespace NS_CH_NAME;
		Application_android* pApp =(Application_android*)Application_android::GetInstancePtr();
		pApp->AppInit(activity,savedState,savedStateSize);
}


#endif