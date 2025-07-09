#include <sys/stat.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void){
    int fd;
    char * text = "hello world!\n";
    struct flock fl;
    
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

    fl.l_start = 1;             /* Offset where the lock begins */
    fl.l_len = 5;               /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;        /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET;

    if(fcntl(fd, F_SETLK, &fl) == -1){
        printf("Can not set write lock byte 1-5 \n");
    }
    else{
        printf("Set write lock byte 1-5 \n");
    }
    while(1){
        sleep(1);
    }
    close(fd);
    return 0;
}