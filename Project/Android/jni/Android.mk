LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

#LOCAL_MODULE    := HelloChaos
#LOCAL_SRC_FILES := ../../ChaosTest/TestTexture.cpp \
#				   ../../../Source/App/Application.cpp \
#				   ../../../Source/App/android/Application_android.cpp


#LOCAL_CFLAGS    := -std=c++0x -Werror -D__ANDROID=
#LOCAL_LDLIBS	 := -llog -landroid -lEGL

#LOCAL_LDLIBS    := -L$(CH_PATH)/Dependency/android/lib -lfreeimage -lzzip -ldl -llog -lz -lGLESv2 -lfreetype



#LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Include
#LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../..//Dependency/glm940


#LOCAL_WHOLE_STATIC_LIBRARIES := ChoPlatform ChoCommon ChoRender

#include $(BUILD_SHARED_LIBRARY)

$(call import-module,ChoCommon)
$(call import-module,ChoPlatform)
$(call import-module,ChoRender)