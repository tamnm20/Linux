#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    pid_t child_pid;    /* Lưu trong stack frame của main() */
    int counter =2;     /* Lưu trong stack frame của main() */

    printf("Gia tri khoi tao cua counter: %d\n", counter);
    child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){/*Process con*/
            printf("\nIm the child process, counter: %d\n", ++counter);
            printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());
            //sleep(1);
        }
        else{/*Process cha*/
            printf("\nIm the parent process, counter: %d\n", ++counter);
            printf("My PID is: %d\n",getpid());
            while(1);
        }
    }
    else{
        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
    }
    return 0;
}