CC=g++
CFLAGS=-IFramework/Core/Dependencies/include -IFramework/Core/Dependencies/include/AL -IFramework/Core/include -IFramework/Modules/include -I../../Include
LDFLAGS=-lrt -ldl -lpthread  Framework/Modules/lib/libPolycodeUI.a Framework/Core/lib/libPolycore.a Framework/Core/Dependencies/lib/libfreetype.a Framework/Core/Dependencies/lib/liblibvorbisfile.a Framework/Core/Dependencies/lib/liblibvorbis.a Framework/Core/Dependencies/lib/liblibogg.a Framework/Core/Dependencies/lib/libopenal.so Framework/Core/Dependencies/lib/libphysfs.a Framework/Core/Dependencies/lib/libpng15.a Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL -lX11

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