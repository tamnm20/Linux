.PHONY: step1 step2 step3 step4 all clean

step1:
	gcc -E main.c -o main.i
step2:
	gcc -S main.i -o main.S
step3:
	gcc -c main.S -o main.o
step4:
	gcc -o main main.o
all:
	gcc -o main main.c
clean:
	rm -rf main main.i main.S main.o
