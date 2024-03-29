#pragma once


NS_CH_BEG

class Application_android : public Application
{
public:
	enum
	{
		LOOPER_ID_MAIN = 1,

		LOOPER_ID_INPUT = 2,

		LOOPER_ID_USER = 3
	};

enum {
    /**
     * Command from main thread: the AInputQueue has changed.  Upon processing
     * this command, android_app->inputQueue will be updated to the new queue
     * (or NULL).
     */
    APP_CMD_INPUT_CHANGED=0,

    /**
     * Command from main thread: a new ANativeWindow is ready for use.  Upon
     * receiving this command, android_app->window will contain the new window
     * surface.
     */
    APP_CMD_INIT_WINDOW=1,

    /**
     * Command from main thread: the existing ANativeWindow needs to be
     * terminated.  Upon receiving this command, android_app->window still
     * contains the existing window; after calling android_app_exec_cmd
     * it will be set to NULL.
     */
    APP_CMD_TERM_WINDOW=2,

    /**
     * Command from main thread: the current ANativeWindow has been resized.
     * Please redraw with its new size.
     */
    APP_CMD_WINDOW_RESIZED=3,

    /**
     * Command from main thread: the system needs that the current ANativeWindow
     * be redrawn.  You should redraw the window before handing this to
     * android_app_exec_cmd() in order to avoid transient drawing glitches.
     */
    APP_CMD_WINDOW_REDRAW_NEEDED=4,

    /**
     * Command from main thread: the content area of the window has changed,
     * such as from the soft input window being shown or hidden.  You can
     * find the new content rect in android_app::contentRect.
     */
    APP_CMD_CONTENT_RECT_CHANGE=5,

    /**
     * Command from main thread: the app's activity window has gained
     * input focus.
     */
    APP_CMD_GAINED_FOCUS=6,

    /**
     * Command from main thread: the app's activity window has lost
     * input focus.
     */
    APP_CMD_LOST_FOCUS=7,

    /**
     * Command from main thread: the current device configuration has changed.
     */
    APP_CMD_CONFIG_CHANGED=8,

    /**
     * Command from main thread: the system is running low on memory.
     * Try to reduce your memory use.
     */
    APP_CMD_LOW_MEMORY=9,

    /**
     * Command from main thread: the app's activity has been started.
     */
    APP_CMD_START=10,

    /**
     * Command from main thread: the app's activity has been resumed.
     */
    APP_CMD_RESUME=11,

    /**
     * Command from main thread: the app should generate a new saved state
     * for itself, to restore from later if needed.  If you have saved state,
     * allocate it with malloc and place it in android_app.savedState with
     * the size in android_app.savedStateSize.  The will be freed for you
     * later.
     */
    APP_CMD_SAVE_STATE=12,

    /**
     * Command from main thread: the app's activity has been paused.
     */
    APP_CMD_PAUSE=13,

    /**
     * Command from main thread: the app's activity has been stopped.
     */
    APP_CMD_STOP=14,

    /**
     * Command from main thread: the app's activity is being destroyed,
     * and waiting for the app thread to clean up and exit before proceeding.
     */
    APP_CMD_DESTROY=15,
};

public:
	Application_android(void);
	virtual ~Application_android(void);
public:
	void AppInit(ANativeActivity* activity,void* savedState, size_t savedStateSize);

private:
	inline NativeWindow_android* GetNativeWindow() { return (NativeWindow_android*)m_pWindows; }
	void ProcessEvent(ASensorEvent* event);
	void ProcessSysEvent(void);
	void PreProcessSysCmd(int8 cmd);
	void PostProcessSysCmd(int8 cmd);

	void AppWriteCmd(int8_t cmd);
	int8_t AppReadCmd();

	static void* RunActivityThread(void* param);
	void RunActive();
	void PrintCurrentConfig();
	void FreeSavedState();
	void SetAppActivityState(int8_t cmd);
	void ReleaseMember();
	IRenderDevice* CreateRender(NativeWindow_android* pWnd);

	void AppSetWindow(ANativeWindow* window);

	void OnInputQueueCreated(AInputQueue* queue);
	void OnInputQueueDestroyed(AInputQueue* queue);
public: //interface 
	virtual void SetOnIdleProc(pfn_OnIdle onIdle,void *pUserParm);
	void SetOnRenderDeviceCreated( pfn_OnRenderDeviceCreated onRenderCreated )
	{m_OnRenderDeviceCreated = onRenderCreated;}

	virtual bool Create(uint nWidth,uint nHeight);
	virtual void Close();
	virtual void Run(void);


private: // 注册给Jvm掉的回调函数
	static void JvmOnDestroy(ANativeActivity* activity);
	static void JvmOnStart(ANativeActivity* activity);
	static void JvmOnResume(ANativeActivity* activity);
	static void* JvmOnSaveInstanceState(ANativeActivity* activity, size_t* outLen);
	static void JvmOnPause(ANativeActivity* activity);
	static void JvmOnStop(ANativeActivity* activity);
	static void JvmOnConfigurationChanged(ANativeActivity* activity);
	static void JvmOnLowMemory(ANativeActivity* activity);
	static void JvmOnWindowFocusChanged(ANativeActivity* activity, int focused);
	static void JvmOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
	static void JvmOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);
	static void JvmOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
	static void JvmOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);

protected:
	ANativeActivity* m_pActivity;
	ASensorManager* m_pSensorManager;
	const ASensor* m_pAccelerometerSensor;
	ASensorEventQueue* m_pSensorEventQueue;
	bool m_bExit;

	NativeWindow_android* m_pPendingWindow;
	NativeWindow_android* m_pWindow;

	void* m_pSaveState;
	size_t m_nSaveStateSize;
	int m_msgread;
	int m_msgwrite;
	AConfiguration* m_pAppConfig;
	ALooper* m_pLooper;

	pthread_t m_thread;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	
	int m_activityState;
	bool m_bStateSaved;

	int m_nWidth,m_nHeight;

	pfn_OnIdle m_pOnIdle;
	void* m_pUserParm;
	
	pfn_OnRenderDeviceCreated m_OnRenderDeviceCreated;

	bool m_bRunning;
};


NS_CH_END