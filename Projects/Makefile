CC=g++
CFLAGS=-IFrameworkCore/Dependencies/include -IFrameworkCore/Dependencies/include/AL -IFrameworkCore/include --ModulesIncDir--
LDFLAGS=-lrt -ldl -lpthread FrameworkCore/lib/libPolycore.a FrameworkCore/Dependencies/lib/libfreetype.a FrameworkCore/Dependencies/lib/liblibvorbisfile.a FrameworkCore/Dependencies/lib/liblibvorbis.a FrameworkCore/Dependencies/lib/liblibogg.a FrameworkCore/Dependencies/lib/libopenal.so FrameworkCore/Dependencies/lib/libphysfs.a FrameworkCore/Dependencies/lib/libpng15.a FrameworkCore/Dependencies/lib/libz.a -lGL -lGLU -lSDL --Modules-- -lX11

default:
	$(CC) $(CFLAGS) main.cpp ../../Source/--ProjectName--.cpp -o --ProjectName-- $(LDFLAGS)
	cp Framework/Core/Assets/default.pak .
	cp Framework/Core/Assets/hdr.pak .
clean:
	rm --ProjectName--
	rm default.pak
	rm hdr.pak
	
