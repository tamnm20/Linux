#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    pid_t child_pid;    /* Lưu trong stack frame của main() */
    int status;
    child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){/*Process con*/
            //sleep(1);
            printf("Im the child process. My PID is: %d\n",getpid());
            while(1);
        }
        else{/*Process cha*/
            printf("Im the parent process. My PID is: %d\n",getpid());
            //while(1);
            wait(&status);
        }
    }
    else{
        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
    }
    return 0;
}