LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := ChoPlatform

LOCAL_CFLAGS    := -std=c++0x -D__ANDROID=
#LOCAL_LDLIBS	:= -llog -landroid 

LOCAL_SRC_FILES := ../../Source/Platform/Tracer.cpp \
                   ../../Source/Platform/Window.cpp \
				   ../../Source/Platform/FileSystem.cpp \
				   ../../Source/Platform/FileStream.cpp \
				   ../../Source/Platform/FileDirectory.cpp \
				   ../../Source/Platform/android/NativeWindow_android.cpp \
                  ../../Source/Platform/android/FileSystem/FileDirectory_android.cpp\
				  ../../Source/Platform/android/FileSystem/FileStream_android.cpp\
				  ../../Source/Platform/android/FileSystem/FileSystem_android.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Source

include $(BUILD_STATIC_LIBRARY)

