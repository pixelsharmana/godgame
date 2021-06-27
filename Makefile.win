CC = g++
CFLAGS = -O3 -fomit-frame-pointer -fexpensive-optimizations -ffast-math
VFLAGS = --std=c++17
LDFLAGS = -pthread -lstdc++fs -lsfml-graphics -lsfml-window -lsfml-system -lGL
CDFLAGS = -g -pg
ASAN = -fsanitize=address
LDFLAGSWIN = -L SFML\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lgdi32 -lwinmm -lfreetype -lole32 -loleaut32 -limm32 -lversion
INCLUDE = -I imgui -I imgui-sfml
INCLUDEWIN = -I SFML\include $(INCLUDE)
WARNINGS = -Wall -Weffc++ -Wextra -Winit-self -Wzero-as-null-pointer-constant -Wnon-virtual-dtor -Winline -Wmissing-declarations -Wmissing-include-dirs -Wundef -Wredundant-decls -Wfloat-equal -Wmain -Wunreachable-code -Wshadow -Wcast-align -W
TARGET = godgame.exe
CPP = *.cpp imgui\\*.cpp imgui-sfml\imgui-SFML.cpp
COMPILATIONWIN = $(CC) $(VFLAGS) $(CFLAGS) -DSFML_STATIC $(INCLUDEWIN) $(LDFLAGSWIN)


all: imgui main
	$(CC) $(VFLAGS) $(CFLAGS) *.o -o $(TARGET) $(LDFLAGSWIN) $(INCLUDEWIN)

main: terrain
	$(COMPILATIONWIN) main.cpp -c

view:
	$(COMPILATIONWIN) view.cpp -c

terrain: tile view
	$(COMPILATIONWIN) terrain.cpp -c

tile:
	$(COMPILATIONWIN) tile.cpp -c

imgui:
	$(COMPILATIONWIN) imgui\\*cpp imgui-sfml\imgui-SFML.cpp -c

debug:
	$(CC) $(WARNINGS) $(VFLAGS) $(ASAN) $(CDFLAGS) $(INCLUDE) $(CPP) $(LDFLAGS) -o $(DTARGET)

clean:
	rm -rf $(TARGET) $(DTARGET)