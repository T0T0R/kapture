EXEC=hello

all: kapture

kapture:
	gcc -o bin/kapture src/*.c -lSDL2 -ggdb

run: all
	bin/kapture
