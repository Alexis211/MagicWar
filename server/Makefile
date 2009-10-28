.PHONY: clean, mrproper

CC = gcc
CPPC = g++
CFLAGS =  
OutFile = magicwar-server
Objects = main.o

all: $(Objects)
	$(CC) $^ -o $(OutFile) -lstdc++ -lpthread

rebuild: mrproper all

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CPPC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.bak
	rm -rf *.o

mrproper: clean
	rm -rf $(OutFile)
