#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */


    //printf("Run command <ls -lah> after 2 seconds\n");
    //sleep(2);
    //execl("/bin/ls", "ls", "-l", "-a", "-h", NULL);
    int i=0;
    while(1){
        printf("Stream %d\n",i++);
        sleep(2);
    }
    return 0;
}