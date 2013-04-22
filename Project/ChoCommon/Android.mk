LOCAL_PATH:= $(call my-dir)


CH_COMMON_SOURCE := $(CH_SOURCE)/Common

include $(CLEAR_VARS)
LOCAL_MODULE := ChoCommon

LOCAL_CFLAGS    := -std=c++0x -DCH_LINUX= -DCH_ANDROID=

LOCAL_SRC_FILES := $(CH_COMMON_SOURCE)/MemoryManager.cpp \
                   $(CH_COMMON_SOURCE)/MemoryPool.cpp \
				   $(CH_COMMON_SOURCE)/String.cpp \
				   $(CH_COMMON_SOURCE)/StringUtl.cpp \
				   $(CH_COMMON_SOURCE)/Math.cpp \
				   $(CH_COMMON_SOURCE)/Object.cpp \
				   $(CH_COMMON_SOURCE)/ReferencedObject.cpp \
				   $(CH_COMMON_SOURCE)/TSReferencedObject.cpp 
                   
LOCAL_C_INCLUDES := $(CH_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(CH_PATH)/Dependency/glm940

include $(BUILD_STATIC_LIBRARY)

