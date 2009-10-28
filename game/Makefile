.PHONY: clean, mrproper

CC = gcc
CPPC = g++
CFLAGS = -g -I .
OutFile = magicwar
Objects = engine/main.o engine/Parser.o engine/functions.o iface2d/Interface2D.o iface3d/Interface3D.o \
		  engine/ressources/UnitType.o engine/ressources/Amelioration.o

all: $(Objects)
	$(CC) $^ -o $(OutFile) -lGL -lIL -lGLU -lglut -lXxf86vm -lpthread -lsfml-system -lsfml-window -lsfml-graphics

rebuild: mrproper all

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CPPC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf */*.bak
	rm -rf */*.o

mrproper: clean
	rm -rf $(OutFile)