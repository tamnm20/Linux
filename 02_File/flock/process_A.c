#include <sys/stat.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void){
    int fd;
    char * text = "hello world!\n";
    if((fd=open("./text.txt", O_RDWR|O_CREAT, 0666)) == -1){
        printf("Can not creat file \n");
        return 0;
    }
    else{
        printf("Creat file text.txt \n");
    }
    if(write(fd, text, strlen(text)) == -1){
        printf("Can not write file \n");
        return 0;
    }
    else{
        printf("write file OK\n");
    }
    if(flock(fd, LOCK_SH) == -1){
        printf("Can not set read lock \n");
    }
    else{
        printf("Set read lock \n");
    }
    while(1){
        sleep(1);
    }
    close(fd);
    return 0;
}