#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    ssize_t bytesWritten;
    const char *data = "Hello, World!\n";

    // Mở file.txt để ghi (tạo file nếu chưa tồn tại)
    fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Ghi dữ liệu vào file
    bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    printf("Wrote %zd bytes to file.txt\n", bytesWritten);

    if (lseek(fd, 7, SEEK_SET) == (off_t) -1) {
        perror("Error using lseek");
        close(fd);
        return 1;
    }
    const char *data1 = "Hello, Tam!\n";
    // Ghi dữ liệu vào file
    bytesWritten = write(fd, data1, strlen(data1));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Wrote %zd bytes to file.txt\n", bytesWritten);

    lseek(fd, -1, SEEK_END);
    write(fd, "Quang Thao Peter.\n", strlen("Quang Thao Peter.\n"));

    lseek(fd, 6, SEEK_CUR);
    write(fd, "ABC.\n", strlen("ABC.\n"));
    // Đóng file
    close(fd);
    return 0;
}

