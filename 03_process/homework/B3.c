#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    pid_t child_pid;    /* Lưu trong stack frame của main() */
    int status, rv;     /* Lưu trong stack frame của main() */

    child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){/*Process con*/
            printf("\nIm the child process\n");
            printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());
            while(1);
            sleep(5);
            _exit(0);
        }
        else{/*Process cha*/
            rv = waitpid(child_pid, &status, 0);
            if(rv == -1){
                printf("wait() unsuccessful\n");
            }

            printf("\nIm the parent process, PID child process: %d\n", rv);
            if(WIFEXITED(status)){
                printf("Normally termination, status = %d\n",WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)){
                printf("killed by signal, value = %d\n", WTERMSIG(status));
            }
        }
    }
    else{
        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
    }
    return 0;
}