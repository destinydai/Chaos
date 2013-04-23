#pragma once

#define CH_PLATFORM_WINDOWS 1
#define CH_PLATFORM_ANDROID 2
#define CH_PLATFORM_MACOS 3




#ifdef WIN32
#define CH_PLATFORM CH_PLATFORM_WINDOWS
#endif

#ifdef __ANDROID
#define CH_PLATFORM CH_PLATFORM_ANDROID
#endif

#ifdef __MACOS
#define CH_PLATFORM CH_PLATFORM_MACOS
#endif

#define NS_CH_NAME Chaos

//define name space
#define NS_CH_BEG namespace NS_CH_NAME {
#define NS_CH_END }

#define CH_SFDEL(x) if((x)!=nullptr){ delete (x); (x)=nullptr; }
#define CH_SFDELARR(x) if((x)!=nullptr) { delete [] (x); (x)=nullptr; }

#define CH_STRING(x) #x

#define CH_BUFSIZE 1024

//common include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <cstddef>
#include <vector>
#include <map>
#include <set>
#include <memory>


using std::string;
using std::vector;
using std::map;
using std::set;
using std::swap;

//include platform api
#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#include <jni.h>
#include <android/log.h>
#include <unistd.h>
#include <sys/atomics.h>
#include <sys/resource.h>
#include <poll.h>
#include <pthread.h>
#include <sched.h>
#include <android/configuration.h>
#include <android/looper.h>
#include <android/native_activity.h>
#include <android/sensor.h>
#include <semaphore.h>
#include <Platform/android/Helper.h>
#elif CH_PLATFORM == CH_PLATFORM_MACOS

#else
#error unknow platform. did you forget specify the platform macro?
#endif


NS_CH_BEG
typedef char byte;
typedef char int8;
typedef wchar_t wchar;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef unsigned int uint;
typedef int64_t int64;
typedef uint64_t uint64;
typedef int32 boolean;
NS_CH_END 


#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#pragma warning(disable:4996)
#pragma warning(disable:4244)	//从“const double”转换到“float”，可能丢失数据
#endif 

#define CH_TRACE(...)  \
if(NS_CH_NAME::Tracer::GetInstancePtr())\
{\
	NS_CH_NAME::Tracer::GetInstancePtr()->Write(__VA_ARGS__);\
}

#if CH_PLATFORM == CH_PLATFORM_WINDOWS
#define CH_ASSERT(x,...)  if(!(x)){__asm{int 3}}
#define CH_ERROR(...) \
if(NS_CH_NAME::Tracer::GetInstancePtr())\
{\
	NS_CH_NAME::Tracer::GetInstancePtr()->WriteError(__VA_ARGS__);\
}\
{__asm{int 3}}
//ANDROID
#elif CH_PLATFORM == CH_PLATFORM_ANDROID
#define CH_ASSERT(x,...) if(!(x)){__android_log_assert(#x,"Chaos Engine","");}
#define CH_ERROR(...) \
if(NS_CH_NAME::Tracer::GetInstancePtr())\
{\
NS_CH_NAME::Tracer::GetInstancePtr()->WriteError(__VA_ARGS__);\
}\
__android_log_assert("error","Chaos Engine","");
//MACOS
#elif CH_PLATFORM == CH_PLATFORM_MACOS

#endif
