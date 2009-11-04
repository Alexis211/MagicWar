.PHONY: clean, mrproper

CC = gcc
CPPC = g++
CFLAGS = -g -I . -std=c++0x -Wall
LD = gcc
LDFLAGS = -lstdc++ -lGL -lGLU -lXxf86vm -lsfml-system -lsfml-window -lsfml-graphics

OutFile = magicwar
Objects = engine/main.o engine/Parser.o engine/functions.o iface2d/Interface2D.o iface3d/Interface3D.o \
		  engine/ressources/UnitType.o engine/ressources/Amelioration.o engine/ressources/Faction.o \
		  engine/game/Game.o engine/game/Player.o engine/game/Unit.o engine/game/GameThread.o \
          cliface/CLInterface.o cliface/CLInterface-main.o iface2d/Repr2D.o \
		  iface2d/Console.o engine/Calculator.o iface2d/Interface2D-main.o engine/game/Map.o

all: $(Objects)
	$(LD) $^ -o $(OutFile) $(LDFLAGS)

rebuild: mrproper all

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CPPC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf */*.bak
	rm -rf */*.o
	rm -rf */*/*.o

mrproper: clean
	rm -rf $(OutFile)
