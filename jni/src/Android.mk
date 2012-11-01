LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
BOX2D_PATH := ../

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/$(BOX2D_PATH)

LOCAL_SRC_FILES := \
	$(SDL_PATH)/src/main/android/SDL_android_main.cpp \
	main.cpp \
	objects/Planet.cpp \
	objects/Sprite.cpp \
	objects/Asteroid.cpp \
	objects/Bomb.cpp \
	Game.cpp \
	Screen.cpp \
	Assets.cpp \
	Object.cpp

LOCAL_SHARED_LIBRARIES := SDL2 Box2D

LOCAL_LDLIBS := -lGLESv1_CM -llog
LOCAL_CPPFLAGS = -std=gnu++0x -frtti

include $(BUILD_SHARED_LIBRARY)
