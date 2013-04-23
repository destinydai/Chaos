LOCAL_PATH:= $(call my-dir)


include $(CLEAR_VARS)

LOCAL_MODULE := ChoRender
LOCAL_CFLAGS    := -std=c++0x -D__ANDROID=

LOCAL_SRC_FILES := ../../Source/Render/RenderDevice.cpp \
                   ../../Source/Render/GL/GLEGL_Android.cpp \
				   ../../Source/Render/GL/GLInputLayout.cpp \
				   ../../Source/Render/GL/GLPixelShader.cpp \
				   ../../Source/Render/GL/GLRenderBase.cpp \
				   ../../Source/Render/GL/GLRenderBuffer.cpp \
				   ../../Source/Render/GL/GLRenderDevice.cpp \
				   ../../Source/Render/GL/GLShader.cpp \
				   ../../Source/Render/GL/GLShaderProgram.cpp \
				   ../../Source/Render/GL/GLShaderVariable.cpp \
				   ../../Source/Render/GL/GLShaderVertexAttribute.cpp \
				   ../../Source/Render/GL/GLTexture2D.cpp \
				   ../../Source/Render/GL/GLVertexShader.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Dependency/glm940
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Dependency/android/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Source

LOCAL_WHOLE_STATIC_LIBRARIES := zzip freeimage

include $(BUILD_STATIC_LIBRARY)

$(call import-module,freeimage)






