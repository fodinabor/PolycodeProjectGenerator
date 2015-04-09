CC=g++
CFLAGS=-IFrameworkCore/Dependencies/include -IFrameworkCore/Dependencies/include/AL -IFrameworkCore/include -IFramework/Modules/include 
LDFLAGS=-lrt -ldl -lpthread FrameworkCore/lib/libPolycore.a FrameworkCore/Dependencies/lib/libfreetype.a FrameworkCore/Dependencies/lib/liblibvorbisfile.a FrameworkCore/Dependencies/lib/liblibvorbis.a FrameworkCore/Dependencies/lib/liblibogg.a FrameworkCore/Dependencies/lib/libopenal.so FrameworkCore/Dependencies/lib/libphysfs.a FrameworkCore/Dependencies/lib/libpng15.a FrameworkCore/Dependencies/lib/libz.a -lGL -lGLU -lSDL  Framework/Modules/lib/libPolycodeUI.a -lX11

default:
	$(CC) $(CFLAGS) main.cpp ../../Source/PolycodeProjectGenerator.cpp -o PolycodeProjectGenerator $(LDFLAGS)
	cp Framework/Core/Assets/default.pak .
	cp Framework/Core/Assets/hdr.pak .
	cp ../../UIThemes.pak .
	cp -R ../../Projects .
clean:
	rm PolycodeProjectGenerator
	rm default.pak
	rm hdr.pak
	rm UIThemes.pak
	rm -R Projects