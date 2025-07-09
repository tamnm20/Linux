#include <sys/stat.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>

int main(void){
    int fd;
    char buf[20] = {0};
    if((fd=open("./text.txt", O_RDWR)) == -1){
        printf("Can not open file \n");
        return 0;
    }
    else{
        printf("Open file text.txt \n");
    }
    if(flock(fd, LOCK_EX | LOCK_NB) == -1){
        printf("Can not get write lock \n");
    }

    if(flock(fd, LOCK_SH | LOCK_NB) == -1){
        printf("Can not get read lock \n");
    }
    else{
        printf("Get read lock file \n");
        if(read(fd, buf, sizeof(buf) -1) == -1){
            printf("Can not read file \n");
            return 0;
        }
        else{
            printf("%s", buf);
        }
    }
    close(fd);
    return 0;
}