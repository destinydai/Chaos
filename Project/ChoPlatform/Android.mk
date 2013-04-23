LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ChoPlatform

LOCAL_CFLAGS    := -std=c++0x -D__ANDROID=
#LOCAL_LDLIBS	:= -llog -landroid 

LOCAL_SRC_FILES := ../../Source/Platform/Tracer.cpp \
                   ../../Source/Platform/Window.cpp \
				   ../../Source/Platform/android/NativeWindow_android.cpp 
                  

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Source

include $(BUILD_STATIC_LIBRARY)

