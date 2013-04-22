#include "stdafx.h"


NS_CH_BEG

Window_android::Window_android( ANativeActivity* activity,void* savedState, size_t savedStateSize ):
	m_pWnd(0),
	m_pActivity(activity),
	m_pSaveState(0),
	m_nSaveStateSize(savedStateSize),
	m_msgread(0),
	m_msgwrite(0),
	m_notifyEvent(true,false),
	m_pAppConfig(0)
{
	if(savedStateSize <=0)
	{
		CH_ERROR("[pl] error: the savedStateSize=%d is invalid",savedStateSize);
	}
	m_pSaveState = new char[savedStateSize];
	memccpy(m_pSaveState,savedState,savedStateSize);

	int msgpipe[2];
	if(pipe(msgpipe))
	{
		CH_ERROR("[pl] error: call pipe failed in Window_android::Window_android, could not create pipe:%s",strerror(errno));
		return;
	}

	m_msgread = msgpipe[0];
	m_msgwrite = msgpipe[1];

	if(!m_thread.startThread(Window_android::RunActivityThread,this))
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

Window_android::~Window_android( void )
{
	if(m_pSaveState)
	{
		CH_SFDELARR((char*)m_pSaveState);
	}
}

void Window_android::OnNativeWindowCreated( ANativeActivity* activity, ANativeWindow* pWnd )
{
	CH_TRACE("[pl] info: Android native window create succeed");
	CriticalSection::ScopeLock locker(m_msgLock);

	if(m_pWnd != nullptr)
	{

	}
}

void Window_android::RunActivityThread( void* pData )
{
	Window_android* pWind = (Window_android*)pData;
	pWind->RunActivity();
}

void Window_android::RunActivity()
{
	m_pAppConfig = AConfiguration_new();
	AConfiguration_fromAssetManager(m_pAppConfig,m_pActivity->assetManager);

	PrintCurrentConfig();



}

void Window_android::PrintCurrentConfig()
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


NS_CH_END


static void onDestroy(ANativeActivity* activity) {
		android_app_free((struct android_app*)activity->instance);
}

static void onStart(ANativeActivity* activity) {
	android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_START);
}

static void onResume(ANativeActivity* activity) {
	android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_RESUME);
}

static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen) {
	struct android_app* android_app = (struct android_app*)activity->instance;
	void* savedState = NULL;

	pthread_mutex_lock(&android_app->mutex);
	android_app->stateSaved = 0;
	android_app_write_cmd(android_app, APP_CMD_SAVE_STATE);
	while (!android_app->stateSaved) {
		pthread_cond_wait(&android_app->cond, &android_app->mutex);
	}

	if (android_app->savedState != NULL) {
		savedState = android_app->savedState;
		*outLen = android_app->savedStateSize;
		android_app->savedState = NULL;
		android_app->savedStateSize = 0;
	}

	pthread_mutex_unlock(&android_app->mutex);

	return savedState;
}

static void onPause(ANativeActivity* activity) {
	android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_PAUSE);
}

static void onStop(ANativeActivity* activity) {
	android_app_set_activity_state((struct android_app*)activity->instance, APP_CMD_STOP);
}

static void onConfigurationChanged(ANativeActivity* activity) {
	struct android_app* android_app = (struct android_app*)activity->instance;
	android_app_write_cmd(android_app, APP_CMD_CONFIG_CHANGED);
}

static void onLowMemory(ANativeActivity* activity) {
	struct android_app* android_app = (struct android_app*)activity->instance;
	android_app_write_cmd(android_app, APP_CMD_LOW_MEMORY);
}

static void onWindowFocusChanged(ANativeActivity* activity, int focused) {
	Window_android* pWind = (Window_android*) activity->instance;
	android_app_write_cmd((struct android_app*)activity->instance, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window) {
	android_app_set_window((struct android_app*)activity->instance, window);
}

static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window) {
	android_app_set_window((struct android_app*)activity->instance, NULL);
}

static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue) {
	android_app_set_input((struct android_app*)activity->instance, queue);
}

static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue) {
	android_app_set_input((struct android_app*)activity->instance, NULL);
}

void ANativeActivity_onCreate(ANativeActivity* activity,void* savedState, size_t savedStateSize) 
{
		activity->callbacks->onDestroy = onDestroy;
		activity->callbacks->onStart = onStart;
		activity->callbacks->onResume = onResume;
		activity->callbacks->onSaveInstanceState = onSaveInstanceState;
		activity->callbacks->onPause = onPause;
		activity->callbacks->onStop = onStop;
		activity->callbacks->onConfigurationChanged = onConfigurationChanged;
		activity->callbacks->onLowMemory = onLowMemory;
		activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
		activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
		activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
		activity->callbacks->onInputQueueCreated = onInputQueueCreated;
		activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

		activity->instance = NS_CH_NAME::Window_android(activity, savedState, savedStateSize);
}