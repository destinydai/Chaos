#pragma once


NS_CH_BEG

class NativeWindow_android;
class NativeAssetManager_android;

class NativeActivity_android 
{
public:
	enum
	{
		LOOPER_ID_MAIN = 1,

		LOOPER_ID_INPUT = 2,

		LOOPER_ID_USER = 3
	};

	struct ActivityCallbacks
	{
		 /**
     * NativeActivity has started.  See Java documentation for Activity.onStart()
     * for more information.
     */
    void (*onStart)(NativeActivity_android* activity);
    
    /**
     * NativeActivity has resumed.  See Java documentation for Activity.onResume()
     * for more information.
     */
    void (*onResume)(NativeActivity_android* activity);
    
    /**
     * Framework is asking NativeActivity to save its current instance state.
     * See Java documentation for Activity.onSaveInstanceState() for more
     * information.  The returned pointer needs to be created with malloc();
     * the framework will call free() on it for you.  You also must fill in
     * outSize with the number of bytes in the allocation.  Note that the
     * saved state will be persisted, so it can not contain any active
     * entities (pointers to memory, file descriptors, etc).
     */
    void* (*onSaveInstanceState)(NativeActivity_android* activity, size_t* outSize);
    
    /**
     * NativeActivity has paused.  See Java documentation for Activity.onPause()
     * for more information.
     */
    void (*onPause)(NativeActivity_android* activity);
    
    /**
     * NativeActivity has stopped.  See Java documentation for Activity.onStop()
     * for more information.
     */
    void (*onStop)(NativeActivity_android* activity);
    
    /**
     * NativeActivity is being destroyed.  See Java documentation for Activity.onDestroy()
     * for more information.
     */
    void (*onDestroy)(NativeActivity_android* activity);

    /**
     * The current device AConfiguration has changed.  The new configuration can
     * be retrieved from assetManager.
     */
    void (*onConfigurationChanged)(NativeActivity_android* activity);

    /**
     * The system is running low on memory.  Use this callback to release
     * resources you do not need, to help the system avoid killing more
     * important processes.
     */
    void (*onLowMemory)(NativeActivity_android* activity);
	} ;

	void (*Pfn_MainLoop)();

public:
	NativeActivity_android(ANativeActivity* activity,void* savedState, size_t savedStateSize,Pfn_MainLoop pLoopMian);
	virtual ~NativeActivity_android(void);

public:
	
	NativeWindow_android* GetWindowPtr() { return m_pWindow; }
	NativeAssetManager_android* GetAssetManagerPtr() {return m_pAssetManager;}

	void* GetBindInstance() { return m_pActivity->instance; }

	void StartActivityThread();

	int8 ReadCmd();
private:
	static void RunActivityThread(void* param);
	void RunActive();
	void PrintCurrentConfig();
	void FreeSavedState();
protected:
	ANativeActivity *m_pActivity;
	NativeWindow_android *m_pWindow;
	NativeAssetManager_android* m_pAssetManager;
	void* m_pSaveState;
	size_t m_nSaveStateSize;
	int m_msgread;
	int m_msgwrite;
	ThreadEvent m_notifyEvent;
	Thread m_thread;
	AConfiguration* m_pAppConfig;
	CriticalSection m_lock;
	ALooper* m_pLooper;
	Pfn_MainLoop m_pMainLoopFunction;
};

NS_CH_END