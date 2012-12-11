all: jni/src/gitversion.h jni/src/Assets.cpp
	ndk-build
	ant debug

release: jni/src/gitversion.h jni/src/Assets.cpp
	ndk-build
	ant release

send:
	adb install -r bin/Peli-debug.apk

run:
	ndk-gdb --start

jni/src/Assets.cpp:
	jni/src/build-assets.py
	mv Assets.cpp jni/src/Assets.cpp

jni/src/gitversion.h: .git/HEAD .git/index
	echo "#define GITVERSION \"$(shell git describe --always --dirty)\"" > $@
