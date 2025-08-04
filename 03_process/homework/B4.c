#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>


void writefile (int fd, char * a){
    // Ghi dữ liệu vào file
    ssize_t bytesWritten;
    bytesWritten = write(fd, a, strlen(a));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return;
    }
    printf("Wrote %zd bytes to file.txt\n", bytesWritten);
}

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    pid_t B_pid, C_pid;    /* Lưu trong stack frame của main() */
    int status, rv;     /* Lưu trong stack frame của main() */
    int fd;

    fd = open("file.txt", O_CREAT | O_WRONLY, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    B_pid = fork();
    if(B_pid >= 0){
        if(B_pid == 0){/*Process con*/
            pid_t B_;
            B_ = fork();
            if(B_ >= 0){
                if(B_ == 0){/*Process con*/
                    printf("\nIm B' process\n");
                    printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());
                    writefile(fd, "Hello I'm B' process\n"); 
                    //while(1);

                    sleep(1);
                    _exit(0);
                }
                else{/*Process cha*/
                    sleep(1);

                    rv = waitpid(B_, &status, 0);
                    if(rv == -1){
                        printf("wait() unsuccessful\n");
                    }
                    printf("\nIm B process\n");
                    printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());

                    writefile(fd, "Hello I'm B process\n"); 
                    //while(1);  
                    //sleep(1);
                    _exit(0);        
                }
            }
            else{
                printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
            }
        }
        else{/*Process cha*/
            sleep(1);
            C_pid = fork();
            if(C_pid >= 0){
                if(C_pid == 0){/*Process con*/
                    pid_t C_;
                    C_ = fork();
                    if(C_ >= 0){
                        if(C_ == 0){/*Process con*/
                            printf("\nIm C' process\n");
                            printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());
                            writefile(fd, "Hello I'm C' process\n"); 
                            //while(1);

                            sleep(1);
                            _exit(0);
                        }
                        else{/*Process cha*/
                            sleep(1);

                            rv = waitpid(C_, &status, 0);
                            if(rv == -1){
                                printf("wait() unsuccessful\n");
                            }
                            printf("\nIm C process\n");
                            printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());

                            writefile(fd, "Hello I'm C process\n"); 
                            //while(1);  
                            sleep(1);
                            _exit(0);        
                        }
                    }
                    else{
                        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
                    }
                }
                else{/*Process cha*/
                    
                }
            }
            else{
                printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
            }
            //sleep(1);
            rv = waitpid(B_pid, &status, 0);
            if(rv == -1){
                printf("wait() unsuccessful\n");
            }
            printf("\nIm A process\n");
            printf("My PID is: %d, PID child process: %d\n",getpid(), rv);
            if(WIFEXITED(status)){
                printf("Normally termination, status = %d\n",WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status)){
                printf("killed by signal, value = %d\n", WTERMSIG(status));
            }
            writefile(fd, "Hello I'm A process\n"); 
            while(1);
        }
    }
    else{
        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
    }
    return 0;
}