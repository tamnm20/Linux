#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
void printFileType(mode_t mode) {
    switch (mode & S_IFMT) {
        case S_IFBLK:   printf("block device\n");       break;
        case S_IFCHR:   printf("character device\n");   break;
        case S_IFDIR:   printf("directory\n");          break;
        case S_IFIFO:   printf("FIFO/pipe\n");          break;
        case S_IFLNK:   printf("symlink\n");            break;
        case S_IFREG:   printf("regular file\n");       break;
        case S_IFSOCK:  printf("socket\n");             break;
        default:        printf("unknown?\n");
    }
}
int main()
{
    int fd;
    char buf[50]={0};
    ssize_t num_re_byte;
    struct stat fileStat;
    const char *filename = "test";
    if (stat(filename, &fileStat) < 0) {
        perror("Error getting file information");
        return 1;
    }
    // Loại file
    printf("File Type: ");
    printFileType(fileStat.st_mode);
    printf("I-node number: %ju\n", fileStat.st_ino);
    // Tên file
    printf("File name: %s\n", filename);

    // Thời gian chỉnh sửa file lần cuối
    printf("Last modification time: %s", ctime(&fileStat.st_mtime));

    // Kích thước file
    printf("File size: %ld bytes\n", fileStat.st_size);

    fd = open("file.txt",O_CREAT | O_RDONLY, 0666);
    if(fd == -1)
        printf("Error: open file\n");
    else
    {
        num_re_byte = read(fd, buf, 50);
        if(num_re_byte==-1)
        {
            printf("Error: read file\n");
        }
        else
        {
            printf("%ld bytes is read successfully\n", num_re_byte);
            printf("%s", buf);
        }
    }
    close(fd);
    return 0;
}