#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

#define THRESHOLD 5

pthread_t thread_id1, thread_id2, thread_id3;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
int fd, data_ready = 0;
ssize_t bytesWritten;
struct stat st;


int counter; //shared variable/shared resources/global variable

typedef struct {
    char name[30];
    char dob[30];
    char address[30];
} sinhvien;

sinhvien data ={0};
ssize_t WriteInfo(char * str){
    // Ghi dữ liệu vào file
    bytesWritten = write(fd, str, strlen(str));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return 0;
    }
    return bytesWritten;
}

static void *thr_handle1(void *args){
    pthread_mutex_lock(&lock);
    // critical section
    while (data_ready != 3){
        pthread_cond_wait(&cond3, &lock);
    }
    strncpy(data.name, "Nguyen Minh Tam\n", sizeof(data.name));
    strncpy(data.dob, "22/12/2000\n", sizeof(data.dob));
    strncpy(data.address, "Ha Noi\n", sizeof(data.address));
    // printf("Nhập tên: ");
    // fgets(data.name, sizeof(data.name), stdin);
    // printf("Nhập ngày sinh: ");
    // fgets(data.dob, sizeof(data.dob), stdin);
    // printf("Nhập địa chỉ: ");
    // fgets(data.address, sizeof(data.address), stdin);
    // printf("Nhap thong tin thanh cong, sinh vien: %s\n", data.name);
    data_ready =1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL); //exit
}

static void *thr_handle2(void *args){

    pthread_mutex_lock(&lock);

    while (!data_ready){
        pthread_cond_wait(&cond, &lock);
    }
    // Mở file.txt để ghi (tạo file nếu chưa tồn tại)
    fd = open("thongtinsinhvien.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file");
        pthread_mutex_unlock(&lock);
        pthread_exit(NULL);
    }

    printf("Wrote %zd bytes to file.txt\n", WriteInfo(data.name));
    printf("Wrote %zd bytes to file.txt\n", WriteInfo(data.dob));
    printf("Wrote %zd bytes to file.txt\n", WriteInfo(data.address));
    close(fd);
    data_ready =2;
    pthread_cond_signal(&cond2);

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL); //exit
}

static void *thr_handle3(void *args){

    pthread_mutex_lock(&lock);

    while (data_ready != 2){
        pthread_cond_wait(&cond2, &lock);
    }
    stat("thongtinsinhvien.txt", &st);
    printf("File size: %ld\n", st.st_size);
    ssize_t num_re_byte;
    char *buf = malloc(st.st_size + 1); // +1 cho null terminator
    if (buf == NULL) {
        perror("malloc failed");
    }
    memset(buf, 0, st.st_size + 1);
    fd = open("thongtinsinhvien.txt",O_CREAT | O_RDONLY, 0666);
    if(fd == -1)
        printf("Error: open file\n");
    else
    {
        num_re_byte = read(fd, buf, st.st_size);
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
    free(buf);
    data_ready =3;
    pthread_cond_signal(&cond3);

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL); //exit
}
int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    int ret;
    data_ready = 3;
    if(ret = pthread_create(&thread_id1, NULL, &thr_handle1, NULL)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }

    if(ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }

    if(ret = pthread_create(&thread_id3, NULL, &thr_handle3, NULL)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);
    return 0;
}