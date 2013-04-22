LOCAL_PATH:= $(call my-dir)
CH_JIN_PATH := $(LOCAL_PATH)

include $(LOCAL_PATH)/../../Android.mk


LOCAL_PATH = $(CH_JIN_PATH)
include $(CLEAR_VARS)


$(call import-add-path,$(CH_PATH))

#LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

LOCAL_MODULE    := HelloChaos
LOCAL_SRC_FILES := TestTexture.cpp \
				   ../../../Source/Game/android/Application.cpp


LOCAL_CFLAGS    := -std=c++0x -Werror -DCH_LINUX= -DCH_ANDROID=
LOCAL_LDLIBS    := -L$(CH_PATH)/Dependency/android/lib -lfreeimage -lzzip -ldl -llog -lz -lGLESv2 -lfreetype


LOCAL_C_INCLUDES := $(CH_INCLUDE)
LOCAL_C_INCLUDES += $(CH_JIN_PATH)
LOCAL_C_INCLUDES += $(CH_PATH)/Dependency/glm940


LOCAL_WHOLE_STATIC_LIBRARIES := ChoPlatform
LOCAL_WHOLE_STATIC_LIBRARIES += ChoCommon
LOCAL_WHOLE_STATIC_LIBRARIES += ChoRender


include $(BUILD_SHARED_LIBRARY)

