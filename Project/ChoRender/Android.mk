LOCAL_PATH:= $(call my-dir)

$(warning enter ChoRender project folder)

CH_RENDER_SOURCE := $(CH_SOURCE)/Render

include $(CLEAR_VARS)
LOCAL_MODULE := ChoRender

LOCAL_CFLAGS    := -std=c++0x -DCH_LINUX= -DCH_ANDROID=

LOCAL_SRC_FILES := $(CH_RENDER_SOURCE)/RenderDevice.cpp \
                   $(CH_RENDER_SOURCE)/GL/GLEGL_Android.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLInputLayout.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLPixelShader.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLRenderBase.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLRenderBuffer.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLRenderDevice.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLShader.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLShaderProgram.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLShaderVariable.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLShaderVertexAttribute.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLTexture2D.cpp \
				   $(CH_RENDER_SOURCE)/GL/GLVertexShader.cpp 
                   
LOCAL_C_INCLUDES := $(CH_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(CH_PATH)/Dependency/glm940
LOCAL_C_INCLUDES += $(CH_SOURCE)
LOCAL_C_INCLUDES += $(CH_PATH)/Dependency/android/include


include $(BUILD_STATIC_LIBRARY)








