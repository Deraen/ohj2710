# PELI

## Installation

### Linux

#### Prequisites

CMake takes care of building Box2D.
SDL and SDL2_gfx need to be installed manually (from included sources if
distribution doesn't recent enough packages).

##### Install SDL

	cd jni/SDL
	./configure --prefix=/usr/local
	make -j5
	sudo make install
	cd ../..

##### Install SDL2_gfx

	cd jni/sdl2gfx-code
	./autogen.sh
	./configure --prefix=/usr/local
	make -j5
	sudo make install
	cd ../..

#### The Game

	mkdir release
	cd release
	cmake ..
	make -j5
	./jni/src/peli

##### Debug

	mkdir debug
	cd debug
	cmake CMAKE_BUILD_TYPE=Debug ..
	make -j5
	gdb ./jni/src/peli

### Android

Ndk-build will take care of building prequisites for Android.

Makefile at root of the project will run ndk-build and ant.
Ndk-build compiles c++ code. Ant compiles jave code and packages program into .apk.
It will also try to send .apk to connected Android phone using adb.

	make
