CC=g++
CFLAGS=-IFramework/Core/Dependencies/include -IFramework/Core/Dependencies/include/AL -IFramework/Core/Dependencies/include/freetype2 -IFramework/Core/include -I../../Include --ModulesIncDir--
LDFLAGS=-lrt -ldl -lpthread --Modules-- Framework/Core/lib/libPolycore.a Framework/Core/Dependencies/lib/libfreetype.a Framework/Core/Dependencies/lib/liblibvorbisfile.a Framework/Core/Dependencies/lib/liblibvorbis.a Framework/Core/Dependencies/lib/liblibogg.a Framework/Core/Dependencies/lib/libopenal.so Framework/Core/Dependencies/lib/libphysfs.a Framework/Core/Dependencies/lib/libpng15.a Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL -lX11

default:
	$(CC) $(CFLAGS) main.cpp ../../Source/--ProjectName--.cpp -o --ProjectName-- $(LDFLAGS)
	cp Framework/Core/Assets/default.pak .
	cp Framework/Core/Assets/hdr.pak .
	--ExtraCopy--
clean:
	rm --ProjectName--
	rm default.pak
	rm hdr.pak
	
