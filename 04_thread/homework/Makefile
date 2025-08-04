all: clear build run
build: main.c claudeFix.c
	gcc main.c -o main -pthread
	gcc claudeFix.c -o claudeFix -pthread
run: main
	./main
clear:
	rm -rf main claudeFix thongtinsinhvien.txt
