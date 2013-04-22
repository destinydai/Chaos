LOCAL_PATH:= $(call my-dir)


CH_PLATFORM_SOURCE := $(CH_SOURCE)/Platform/linux

include $(CLEAR_VARS)
LOCAL_MODULE := ChoPlatform

LOCAL_CFLAGS    := -std=c++0x -DCH_LINUX= -DCH_ANDROID=

LOCAL_SRC_FILES := $(CH_PLATFORM_SOURCE)/Tracer.cpp \
                   $(CH_PLATFORM_SOURCE)/Console.cpp 
                  


LOCAL_C_INCLUDES := $(CH_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)

include $(BUILD_STATIC_LIBRARY)

