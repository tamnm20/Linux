all: clear build run
build: main.c
	gcc main.c -o main -pthread
run: main
	./main
clear:
	rm -rf main
