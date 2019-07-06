LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_LDLIBS    := -llog -ljnigraphics
LOCAL_MODULE    := hook
APP_PROJECT_PATH:= LOCAL_PATH
LOCAL_SRC_FILES := hook.cpp
LOCAL_CFLAGS    =  -ffast-math -O3 -funroll-loops
 
include $(BUILD_SHARED_LIBRARY)
