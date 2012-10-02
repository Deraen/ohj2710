all:
	ndk-build
	ant debug
	adb install -r bin/Peli-debug.apk

run:
	ndk-gdb --start
