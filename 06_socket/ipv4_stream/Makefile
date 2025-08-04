GCC:=/home/phong/Working_Space/BBB/gcc-linaro-6.5.0-2018.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc

all:
	gcc -o server server_stream.c
	gcc -o client client_stream.c
BBB:
	$(GCC) -o client stream_client.c

clean:
	rm -rf client server