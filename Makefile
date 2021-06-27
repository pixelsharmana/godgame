CC = clang++
CFLAGS = -O3 -fomit-frame-pointer -fexpensive-optimizations -ffast-math
VFLAGS = --std=c++17
LDFLAGS = -pthread -lstdc++fs -lsfml-graphics -lsfml-window -lsfml-system -lGL
CDFLAGS = -g -pg
ASAN = -fsanitize=address
INCLUDE = -I imgui -I imgui-sfml
TARGET = godgame
DTARGET = debug_godgame
WARNINGS = -Wall -Weffc++ -Wextra -Winit-self -Wzero-as-null-pointer-constant -Wnon-virtual-dtor -Winline -Wmissing-declarations -Wmissing-include-dirs -Wundef -Wredundant-decls -Wfloat-equal -Wmain -Wunreachable-code -Wshadow -Wcast-align -Wswitch-default -Wswitch-enum
CPP = main.cpp view.cpp tile.cpp terrain.cpp imgui/*cpp imgui-sfml/imgui-SFML.cpp
COMPILATION = $(CC) $(WARNINGS) $(VFLAGS) $(CFLAGS) $(INCLUDE) $(LDFLAGS)

all: imgui main
	$(CC) $(WARNINGS) $(VFLAGS) $(CFLAGS) $(INCLUDE) *.o $(LDFLAGS) -o $(TARGET)

main: terrain
	$(COMPILATION) main.cpp -c

view:
	$(COMPILATION) view.cpp -c

terrain: tile view
	$(COMPILATION) terrain.cpp -c

tile:
	$(COMPILATION) tile.cpp -c

imgui:
	$(COMPILATION) imgui/*cpp imgui-sfml/imgui-SFML.cpp -c

debug:
	$(CC) $(WARNINGS) $(VFLAGS) $(ASAN) $(CDFLAGS) $(INCLUDE) $(CPP) $(LDFLAGS) -o $(DTARGET)

clean:
	rm -rf $(TARGET) $(DTARGET)
