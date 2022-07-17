CFLAGS = -I. -lstdc++ -lsquirrel -lsqstdlib -lm --std=c++17

WINDEFS = -DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__ -D_WIN32 -Wl,-subsystem,windows

WINLIBS = -lstdc++ -lgcc -lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32

SRC = main.cpp

DEPS = main.h

OBJ = main.o



%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)

linux: $(DEPS)
	g++ -o squirrelvm $(SRC) $(CFLAGS) -O2

windows: $(DEPS)
	x86_64-w64-mingw32-g++-win32 -o squirrelvm.exe $(SRC) -lmingw32  $(CFLAGS) $(WINDEFS) $(WINLIBS)

gcw0: $(DEPS)
	mipsel-gcw0-linux-uclibc-g++ -o squirrelvm.dge $(SRC) -mips32 -D_DINGUX -I/opt/gcw0-toolchain/usr/include $(CFLAGS) -L/opt/gcw0-toolchain/usr/lib -L/opt/gcw0-toolchain/usr/lib/gcc/mipsel-gcw0-linux-uclibc/4.9.1 -O2

clean:
	rm *.o

debug: $(DEPS)
	g++ -o squirrelvm $(SRC) $(CFLAGS) -g