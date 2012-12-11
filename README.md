# PELI

This is the source code for a game I wrote for Game programming course (http://www.cs.tut.fi/~peliohj/)
at Tampere University of Techology.

Source written by me can be found at following directories:
- jni/src/
- src/org/oh2710/

## Notices

- The Game gets slow when number of asteroids increases because the gravitation
  computation (Game::Step) needs n^2 time.
- The Game can't be closed easily on Android. Killing C++ main loop doesn't close
  Android window.
- JSON asset system for objects was developed at the beginning of development.
  - It's not used on all parts of code (properties of levels, bombs etc.)
    because I had not enough time.
  - Build-assets.py will generate a .cpp-file from .json files (embedding images etc).
    I chose this solution so that there would be no need for file access
    (eg. where the hell do asset files go?) on Android. However,
    I later noticed that SDL has IO api that works fine on Android.

## Installation

### Linux

#### Prequisites

CMake takes care of building Box2D.
SDL, SDL2_gfx and SDL2_ttf need to be installed manually (from included sources if
distribution doesn't offer recent enough packages).

##### Install SDL

	cd jni/SDL
	mkdir build
	cd build
	../configure --prefix=/usr/local
	make -j5
	sudo make install
	cd ../../..

##### Install SDL2_gfx

	cd jni/sdl2gfx-code
	mkdir build
	cd build
	../configure --prefix=/usr/local
	make -j5
	sudo make install
	cd ../../..

#### Install SDL_ttf

	cd jni/SDL_ttf
	mkdir build
	cd build
	../configure --prefix=/usr/local
	make -j5
	sudo make install
	cd ../../..

#### The Game

	mkdir release
	cd release
	cmake ..
	make -j5
	./peli

##### Debug

	mkdir debug
	cd debug
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j5
	gdb ./peli

### Android

Prequisites: Android SDK and NDK.

First

	android update project

Ndk-build will take care of building Box2D / SDL for Android.

Makefile at root of the project will run ndk-build and ant.
Ndk-build compiles c++ code. Ant compiles jave code and packages program into .apk.
Make will also try to send .apk to connected Android phone using adb.

	make

## About the game

### Modes

#### Normal [LVL1,2,3]

Player has lives (shown on topleft corner). They will be reduced if asteroid
or bomb hits planet. Game will end if lives reach zero.

Player has limited number of weapons.

#### INF [N+1]

Player has points. Player will get points for destroying Asteroids.
Game goes on forever.

Weapons recharge over time. There is cap for weapons.

### Weapons

On desktop the weapons can be selected with keys 1 to 4.

#### Normal

Detonates one asteroid. Other asteroids will go through the explosion unharmed.
Slightly heavier than others.

#### Splash

Creates big explosion when it hits asteroid. Other asteroids that pass through
explosion get destroyed.

#### Chain

Detonates one asteroid. If another asteroid passes through the explosion
it'll explode continuing the chain.

#### Laser

Short laser beam. Easy to control and destroys everything that passes through it.

## Graphic sources

### Planets
- http://en.wikipedia.org/wiki/File:FullMoon2010.jpg
- http://en.wikipedia.org/wiki/File:The_Earth_seen_from_Apollo_17.jpg
- http://en.wikipedia.org/wiki/File:Jupiter_by_Cassini-Huygens.jpg
- http://en.wikipedia.org/wiki/File:DeathStar2.jpg

### Font
- http://www.dafont.com/visitor.font