LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
BOX2D_PATH := ../Box2D

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(BOX2D_PATH)

LOCAL_SRC_FILES := \
	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	main.cpp \
	Object.cpp \
	managers/DrawableManager.cpp \
	objects/Player.cpp \
	objects/Planet.cpp \
	objects/Drawable.cpp \

LOCAL_SHARED_LIBRARIES := SDL2 Box2D

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
