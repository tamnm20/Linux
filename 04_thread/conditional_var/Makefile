all: clear build run
build: main.c con_var.c
	gcc main.c -o main -pthread
	gcc con_var.c -o con_var -pthread
run: main
	./main
clear:
	rm -rf main con_var
