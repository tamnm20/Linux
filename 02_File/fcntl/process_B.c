#include <sys/stat.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void){
    int fd;
    struct flock fl;

    if((fd=open("./text.txt", O_RDWR)) == -1){
        printf("Can not open file \n");
        return 0;
    }
    else{
        printf("Open file text.txt \n");
    }

    fl.l_start = 1;             /* Offset where the lock begins */
    fl.l_len = 5;               /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;        /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET;

    if(fcntl(fd, F_SETLK, &fl) == -1){
        printf("Can not write lock byte 0-5\n");
    }

    fl.l_start = 6;             /* Offset where the lock begins */
    fl.l_len = 6;               /* Number of bytes to lock; 0 means "until EOF" */
    fl.l_type = F_WRLCK;        /* Lock type: F_RDLCK, F_WRLCK, F_UNLCK */
    fl.l_whence = SEEK_SET;

    if(fcntl(fd, F_SETLK, &fl) == -1){
        printf("Can not write lock byte 6-11\n");
    }
    else{
        printf("Set write lock byte 6-11\n");
        lseek(fd, 6, SEEK_SET);

        if(write(fd, "Tam22\n", strlen("Tam22\n")) == -1){
            printf("Can not write file \n");
            return 0;
        }
        else{
            printf("Write file OK\n");
        }
    }
    close(fd);
    return 0;
}