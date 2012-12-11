#!/bin/bash

cd /tmp

if [ ! -d "ohj2710" ]; then
	git clone git://github.com/Deraen/ohj2710.git
	cd ohj2710
else
	cd ohj2710
	original_head=$(git rev-parse HEAD) || exit
	git pull origin || exit
	updated_head=$(git rev-parse HEAD) || exit
fi

if test "$1" = "force" || test "$updated_head" != "$original_head"; then
	VERSION=$(git describe --always --dirty)

	cd ..
	cp -r ohj2710 ohj2710-android
	cp -r ohj2710 ohj2710-x86
	cp -r ohj2710 ohj2710-x86_64

	cd /tmp
	# Android
	cd ohj2710-android
	make

	./github_sendfile.py Peli-$VERSION.apk bin/Peli-debug.apk

	cd /tmp
	# X86_64
	cd ohj2710-x86_64
	mkdir release
	cd release
	cmake ..
	make

	mkdir pkg
	cd pkg
	cp ../peli .
	cp /usr/local/lib/libSDL2-2.0.so.0 /usr/local/lib/libSDL2_gfx-1.0.so.0 /usr/local/lib/libSDL2_ttf-2.0.so.0 .
	cd ..
	tar -acf peli.tar.bz2 pkg

	cd ..

	./github_sendfile.py peli-$VERSION.tar.bz2 release/bin/peli.tar.bz2

	cd ..

	rm -rf ohj2710-*

fi
