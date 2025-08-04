#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    pid_t B_pid;    /* Lưu trong stack frame của main() */
    pid_t C_pid;    /* Lưu trong stack frame của main() */
    int fd;
    ssize_t num_re_byte;
    ssize_t bytesWritten;
    char buf[50]={0};
    int status;

    B_pid = fork();
    if(B_pid >= 0){
        if(B_pid == 0){/*Process con*/
            sleep(1);  
            fd = open("./log/hello.txt", O_RDONLY);
            printf("\nIm process B. ");
            printf("My PID is: %d, my parent PID is: %d\n",getpid(), getppid());
            num_re_byte = read(fd, buf, 50);
            if(num_re_byte==-1)
            {
                printf("Error: read file\n");
            }
            else
            {
                printf("%ld bytes is read successfully\n", num_re_byte);
                printf("%s", buf);
                close(fd);
            }
        }
        else{/*Process cha*/
            printf("\nIm process A\n");
            printf("My PID is: %d\n",getpid()); 
            // Mở file.txt để ghi (tạo file nếu chưa tồn tại)
            fd = open("./log/hello.txt", O_WRONLY | O_CREAT , 0666);
            if (fd == -1) {
                perror("Error opening file");
                return 1;
            }

            // Ghi dữ liệu vào file
            bytesWritten = write(fd, "hello world!\n", strlen("hello world!\n"));
            if (bytesWritten == -1) {
                perror("Error writing to file");
                close(fd);
                return 1;
            }
            printf("Wrote %zd bytes to file.txt\n", bytesWritten);
            close(fd);
            wait(&status);   
            //while(1);
        }
    }
    else{
        printf("fork() unsuccessfully\n"); //fork() return -1 neu loi
    }
    return 0;
}