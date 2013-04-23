LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

LOCAL_MODULE := ChoCommon
LOCAL_CFLAGS    := -std=c++0x -D__ANDROID=

LOCAL_SRC_FILES := ../../Source/Common/MemoryManager.cpp \
                   ../../Source/Common/MemoryPool.cpp \
				   ../../Source/Common/String.cpp \
				   ../../Source/Common/StringUtl.cpp \
				   ../../Source/Common/ChoMath.cpp \
				   ../../Source/Common/Object.cpp \
				   ../../Source/Common/ReferencedObject.cpp \
				   ../../Source/Common/TSReferencedObject.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Include
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Dependency/glm940
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Source

include $(BUILD_STATIC_LIBRARY)

