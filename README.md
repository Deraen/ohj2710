# PELI

## Installation

### Linux

#### Prequisites

CMake takes care of building Box2D.
Freetype2 is required, distribution package should be recent enough.
SDL, SDL2_gfx and SDL_ttf need to be installed manually (from included sources if
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

#### Install SDL_ttf

	cd jni/SDL_ttf
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
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j5
	gdb ./jni/src/peli

### Android

Ndk-build will take care of building prequisites for Android.

Makefile at root of the project will run ndk-build and ant.
Ndk-build compiles c++ code. Ant compiles jave code and packages program into .apk.
It will also try to send .apk to connected Android phone using adb.

	make

## About the game

### Weapons

#### Normal

Detonates one asteroid. Other asteroids will go through the explosion unharmed.

#### Splash

Creates big explosion when it hits asteroid. Other asteroids that pass through
explosion get destroyed.

#### Chain

Detonates one asteroid. If another asteroid passes through the explosion
it'll explode continuen the chain.

#### Laser

Short laser beam. Easy to control and destroys everything that passes through it.
