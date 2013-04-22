LOCAL_PATH := $(call my-dir)



CH_PROJ := $(LOCAL_PATH)
CH_PATH := $(LOCAL_PATH)/../
CH_SOURCE := $(CH_PATH)Source
CH_INCLUDE := $(CH_PATH)Include

include $(CH_PROJ)/ChoPlatform/Android.mk
include $(CH_PROJ)/ChoCommon/Android.mk
include $(CH_PROJ)/ChoRender/Android.mk