# cc = gcc
# run: blah
# 	./blah
# blah: blah.o
# 	$(cc) blah.o -o blah 
# blah.o: blah.c
# 	$(cc) -c blah.c -o blah.o 
foo := a.o b.o l.a c.o
one := $(patsubst %.o, %.c, $(foo))

all:
	echo $(foo)
	echo $(one)

clean:
	rm -rf ../headers
	rm -f some_binary
