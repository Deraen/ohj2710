all: jni/src/gitversion.h jni/src/Assets.cpp
	ndk-build
	ant debug
	adb install -r bin/Peli-debug.apk

release: jni/src/gitversion.h jni/src/Assets.cpp
	ndk-build
	ant release
	adb install -r bin/Peli-release-unsigned.apk

run:
	ndk-gdb --start

jni/src/Assets.cpp:
	cd jni/src/
	./build-assets.py

jni/src/gitversion.h: .git/HEAD .git/index
	echo "#define GITVERSION \"$(shell git describe --always --dirty)\"" > $@
