all:
	ndk-build
	ant debug
	adb install -r bin/Peli-debug.apk

release:
	ndk-build
	ant release
	adb install -r bin/Peli-release-unsigned.apk

run:
	ndk-gdb --start
