#pragma once


#include "ChoRender.h"

#include "FreeImage.h"

#ifdef CH_PLATFORM_WINDOWS
//#include <GL/glew.h>
//#include <GL/wglew.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#if defined  CH_ANDROID
//#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif





#define  CH_IMPL_RENDER_BASE   \
public:\
	void AddRef() {++m_nRefCount;}\
	void DeRef() { --m_nRefCount; if(m_nRefCount==0){delete this;} }\
	int GetRef() const { return m_nRefCount; }\
	IRenderDevice* GetDevice(){ return m_pRenderDevice; }\
	void SetUserData(void *pData) { m_pUserData=pData; }\
	void* GetUserData() { return m_pUserData; }\
private:\
	IRenderDevice *m_pRenderDevice;\
	void *m_pUserData;\
	int m_nRefCount;

#define CH_RENDER_TRACE_ERROR(pDev,...) ((RenderDevice*)pDev)->SetErrorMessage(__VA_ARGS__); CH_TRACE(__VA_ARGS__);


#include "Render/RenderDevice.h"

//open gl 
#define CH_GLFAILCHECK { GLint error_code=glGetError(); CH_ASSERT(error_code==0,"error:%d GL fail check");}


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
	#include "Render/GL/GLEGL_Win32.h"
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
	#include "Render/GL/GLEGL_Android.h"
#else
	CH_ERROR("not implement yet");
#endif

#include "Render/GL/GLRenderBase.h"
#include "Render/GL/GLShader.h"
#include "Render/GL/GLVertexShader.h"
#include "Render/GL/GLPixelShader.h"
#include "Render/GL/GLShaderProgram.h"
#include "Render/GL/GLRenderDevice.h"
#include "Render/GL/GLRenderBuffer.h"
#include "Render/GL/GLInputLayout.h"
#include "Render/GL/GLShaderVariable.h"
#include "Render/GL/GLShaderVertexAttribute.h"
#include "Render/GL/GLTexture2D.h"

NS_CH_BEG


inline string GetVariableTypeString(RVariableType::Type eType)
{
	switch(eType)
	{
	case RVariableType::BOOL:
		return "bool";
	case RVariableType::BOOL2:
		return "bool2";
	case RVariableType::BOOL3:
		return "bool3";
	case RVariableType::BOOL4:
		return "bool4";
	case RVariableType::INT:
		return "int";
	case RVariableType::INT2:
		return "int2";
	case RVariableType::INT3:
		return "int3";
	case RVariableType::INT4:
		return "int4";
	case RVariableType::FLOAT:
		return "float";
	case RVariableType::VEC2:
		return "vec2";
	case RVariableType::VEC3:
		return "vec3";
	case RVariableType::VEC4:
		return "vec4";
	case RVariableType::MAT2:
		return "mat2";
	case RVariableType::MAT3:
		return "mat3";
	case RVariableType::MAT4:
		return "mat4";
	case RVariableType::SAMPLER_2D:
		return "Sampler2D";
	case RVariableType::SAMPLER_CUBE:
		return "Sampler3D";
	default:
		CH_ASSERT(false,"[rd] error:unhandled shader variable enum type in GetVariableTypeString function.");
		return "";
	}
}

inline GLenum MapPrimitiveTypeToGLType(PrimitiveType::Type eType)
{
	switch(eType)
	{
	case PrimitiveType::POINT_LIST:
		return GL_POINTS;
	case PrimitiveType::LINE_LIST:
		return GL_LINES;
	case PrimitiveType::LINE_STRIP:
		return GL_LINE_STRIP;
	case PrimitiveType::TRIANGLE_LIST:
		return GL_TRIANGLES;
	case PrimitiveType::TRIANGLE_STRIP:
		return GL_TRIANGLE_STRIP;
	default:
		CH_ASSERT(false,"[rd] error: unhandled enum type in MapPrimitiveTypeToGLType function.");
		return 0;
	}
}

inline RVariableType::Type MapGLValueTypeToChValueType(GLenum eGLType )
{
	switch(eGLType)
	{
	case GL_BOOL:
		return RVariableType::BOOL;
	case GL_BOOL_VEC2:
		return RVariableType::BOOL2;
	case GL_BOOL_VEC3:
		return RVariableType::BOOL3;
	case GL_BOOL_VEC4:
		return RVariableType::BOOL4;
	case GL_UNSIGNED_BYTE:
		return RVariableType::UNSIGNED_BYTE;
	case GL_UNSIGNED_SHORT:
		return RVariableType::UNSIGNED_SHORT;
	case GL_UNSIGNED_INT:
		return RVariableType::UNSIGNED_INT;
	case GL_FLOAT: 
		return RVariableType::FLOAT;
	case GL_FLOAT_VEC2:
		return RVariableType::VEC2;
	case GL_FLOAT_VEC3:
		return RVariableType::VEC3;
	case GL_FLOAT_VEC4:
		return RVariableType::VEC4;
	case GL_INT:
		return RVariableType::INT;
	case GL_INT_VEC2:
		return RVariableType::INT2;
	case GL_INT_VEC3:
		return RVariableType::INT3;
	case GL_INT_VEC4:
		return RVariableType::INT4;
	case GL_FLOAT_MAT2:
		return RVariableType::MAT2;
	case GL_FLOAT_MAT3:
		return RVariableType::MAT3;
	case GL_FLOAT_MAT4:
		return RVariableType::MAT4;
	case GL_SAMPLER_2D:
		return RVariableType::SAMPLER_2D;
	case GL_SAMPLER_CUBE:
		return RVariableType::SAMPLER_CUBE;
	default:
		CH_ASSERT(false,"[rd] error: unhandled enum type in MapGLValueTypeToChValueType function.");
		return RVariableType::UNKNOW;
	}
}

inline GLenum MapValueTypeToGLValueType(RVariableType::Type eType)
{
	switch(eType)
	{
	case RVariableType::BOOL:
		return GL_BOOL; 
	case RVariableType::BOOL2:
		return GL_BOOL_VEC2;
	case RVariableType::BOOL3:
		return GL_BOOL_VEC3;
	case RVariableType::BOOL4:
		return GL_BOOL_VEC4;
	case RVariableType::UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case RVariableType::UNSIGNED_SHORT:
		return GL_UNSIGNED_SHORT;
	case RVariableType::UNSIGNED_INT:
		return GL_UNSIGNED_INT;
	case RVariableType::INT:
		return GL_INT;
	case RVariableType::INT2:
		return GL_INT_VEC2;
	case RVariableType::INT3:
		return GL_INT_VEC3;
	case RVariableType::INT4:
		return GL_INT_VEC4;
	case RVariableType::FLOAT:
		return GL_FLOAT;
	case RVariableType::VEC2:
		return GL_FLOAT_VEC2;
	case RVariableType::VEC3:
		return GL_FLOAT_VEC3;
	case RVariableType::VEC4:
		return GL_FLOAT_VEC4;
	case RVariableType::SAMPLER_2D:
		return GL_SAMPLER_2D;
	case RVariableType::SAMPLER_CUBE:
		return GL_SAMPLER_CUBE;
	default:
		CH_ASSERT(false,"[rd] error: unhandled enum type in MapValueTypeToGLValueType function.");
		return 0;
	}
}

inline GLenum MapColorFormatToGLColor(ColorFormat::Type eColor)
{
	switch(eColor)
	{
	case ColorFormat::RGB:
		return GL_RGB;
	case ColorFormat::RGBA:
		return GL_RGBA;
	case ColorFormat::LUMINANCE:
		return GL_LUMINANCE;
	case ColorFormat::LUMINANCE_ALPHA:
		return GL_LUMINANCE_ALPHA;
	case ColorFormat::ALPHA:
		return GL_ALPHA;
	default:
		CH_ASSERT(false,"[rd] error: unhandled enum type in MapColorFormatToGLColor function.");
		return 0;
	}
}
	
NS_CH_END
