rem g++ -fpermissive main.cpp graphics_common.cpp -ILibraries\glad\include -ILibraries\SDL2-devel-2.0.12-mingw\SDL2-devel-2.0\SDL2-2.0.12\x86_64-w64-mingw32\include -LLibraries\SDL2-devel-2.0.12-mingw\SDL2-devel-2.0\SDL2-2.0.12\x86_64-w64-mingw32\lib Libraries\glad\glad.c -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o a.exe

set Libraries=..\..\Libraries
g++ -fpermissive main.cpp -I%Libraries%\glad\include -I%Libraries%\SDL2-devel-2.0.12-mingw\SDL2-devel-2.0\SDL2-2.0.12\x86_64-w64-mingw32\include -L%Libraries%\SDL2-devel-2.0.12-mingw\SDL2-devel-2.0\SDL2-2.0.12\x86_64-w64-mingw32\lib %Libraries%\glad\glad.c -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o a.exe
a.exe