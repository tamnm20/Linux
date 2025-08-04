all: clear build run
build: main.c
	gcc main.c -o main
run: main
	./main
clear:
	rm -rf main exam

sigchld: SIGCHLD.c
	gcc SIGCHLD.c -o exam
	./exam
