#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[50]={0};
    ssize_t num_re_byte;
    fd = open("file.txt",O_CREAT | O_RDONLY, 0666);
    if(fd == -1)
        printf("Error: open file\n");
    else
    {
        num_re_byte = read(fd, buf, 20);
        if(num_re_byte==-1)
        {
            printf("Error: read file\n");
        }
        else
        {
            printf("%ld bytes is read successfully\n", num_re_byte);
            printf("%s\n", buf);
        }
    }
    close(fd);
    return 0;
}