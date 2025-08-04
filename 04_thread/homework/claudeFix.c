#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

#define THRESHOLD 5

pthread_t thread_id1, thread_id2, thread_id3;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_input = PTHREAD_COND_INITIALIZER;   // Cho thread nhập liệu
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER;   // Cho thread ghi file
pthread_cond_t cond_read = PTHREAD_COND_INITIALIZER;    // Cho thread đọc file

int fd;
ssize_t bytesWritten;
struct stat st;

// Trạng thái của chương trình (chu kỳ)
int input_done = 0;   // Thread 1 đã nhập xong
int write_done = 0;   // Thread 2 đã ghi xong
int read_done = 1;    // Thread 3 đã đọc xong (bắt đầu = 1 để thread 1 chạy ngay)

int cycle_count = 0;  // Đếm số chu kỳ

typedef struct {
    char name[30];
    char dob[30];
    char address[30];
} sinhvien;

sinhvien data = {0};

ssize_t WriteInfo(char * str){
    bytesWritten = write(fd, str, strlen(str));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        return 0;
    }
    return bytesWritten;
}

// Thread 1: Nhập thông tin sinh viên (lặp vô hạn)
static void *thr_handle1(void *args){
    while(1) {  // Vòng lặp vô hạn
        pthread_mutex_lock(&lock);
        
        // Chờ thread 3 đọc xong chu kỳ trước
        while (!read_done) {
            pthread_cond_wait(&cond_input, &lock);
        }
        
        cycle_count++;
        printf("\n==================================================\n");
        printf("CHU KỲ %d - THREAD 1: Nhập thông tin sinh viên\n", cycle_count);
        printf("==================================================\n");
        
        // Reset trạng thái cho chu kỳ mới
        read_done = 0;
        input_done = 0;
        write_done = 0;
        
        printf("Nhập tên: ");
        fflush(stdout);
        
        // Unlock để có thể nhập dữ liệu
        pthread_mutex_unlock(&lock);
        fgets(data.name, sizeof(data.name), stdin);
        
        pthread_mutex_lock(&lock);
        printf("Nhập ngày sinh: ");
        fflush(stdout);
        pthread_mutex_unlock(&lock);
        fgets(data.dob, sizeof(data.dob), stdin);
        
        pthread_mutex_lock(&lock);
        printf("Nhập địa chỉ: ");
        fflush(stdout);
        pthread_mutex_unlock(&lock);
        fgets(data.address, sizeof(data.address), stdin);
        
        pthread_mutex_lock(&lock);
        printf("✓ Nhập thông tin thành công cho sinh viên: %s", data.name);
        
        input_done = 1;  // Đánh dấu đã nhập xong
        pthread_cond_signal(&cond_write);  // Báo cho thread 2
        
        pthread_mutex_unlock(&lock);
        
        // Thêm delay nhỏ để tránh CPU spinning
        usleep(100000); // 0.1 giây
    }
    
    pthread_exit(NULL);
}

// Thread 2: Ghi thông tin vào file (lặp vô hạn)
static void *thr_handle2(void *args){
    while(1) {  // Vòng lặp vô hạn
        pthread_mutex_lock(&lock);
        
        // Chờ thread 1 nhập xong
        while (!input_done) {
            pthread_cond_wait(&cond_write, &lock);
        }
        
        printf("\n📝 THREAD 2: Ghi dữ liệu vào file (chu kỳ %d)\n", cycle_count);
        
        // Mở file để ghi (append mode để giữ lịch sử)
        fd = open("thongtinsinhvien.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (fd == -1) {
            perror("Error opening file for writing");
            pthread_mutex_unlock(&lock);
            continue; // Tiếp tục chu kỳ tiếp theo
        }

        // Ghi header cho mỗi entry
        char header[100];
        snprintf(header, sizeof(header), "\n--- Sinh viên #%d ---\n", cycle_count);
        write(fd, header, strlen(header));
        
        printf("✓ Wrote %zd bytes: name\n", WriteInfo(data.name));
        printf("✓ Wrote %zd bytes: dob\n", WriteInfo(data.dob));
        printf("✓ Wrote %zd bytes: address\n", WriteInfo(data.address));
        
        close(fd);
        
        write_done = 1;  // Đánh dấu đã ghi xong
        pthread_cond_signal(&cond_read);  // Báo cho thread 3
        
        pthread_mutex_unlock(&lock);
        
        // Thêm delay nhỏ
        usleep(100000); // 0.1 giây
    }
    
    pthread_exit(NULL);
}

// Thread 3: Đọc và hiển thị nội dung file (lặp vô hạn)
static void *thr_handle3(void *args){
    while(1) {  // Vòng lặp vô hạn
        pthread_mutex_lock(&lock);
        
        // Chờ thread 2 ghi xong
        while (!write_done) {
            pthread_cond_wait(&cond_read, &lock);
        }
        
        printf("\n📖 THREAD 3: Đọc dữ liệu từ file (chu kỳ %d)\n", cycle_count);
        
        // Lấy thông tin kích thước file
        if (stat("thongtinsinhvien.txt", &st) == -1) {
            perror("Error getting file stats");
            pthread_mutex_unlock(&lock);
            continue;
        }
        
        printf("📊 File size: %ld bytes\n", st.st_size);
        
        // Cấp phát bộ nhớ
        char *buf = malloc(st.st_size + 1);
        if (buf == NULL) {
            perror("malloc failed");
            pthread_mutex_unlock(&lock);
            continue;
        }
        memset(buf, 0, st.st_size + 1);
        
        // Mở file để đọc
        fd = open("thongtinsinhvien.txt", O_RDONLY, 0666);
        if(fd == -1) {
            printf("❌ Error: Cannot open file for reading\n");
            free(buf);
            pthread_mutex_unlock(&lock);
            continue;
        }
        
        ssize_t num_read_bytes = read(fd, buf, st.st_size);
        if(num_read_bytes == -1) {
            printf("❌ Error: Cannot read file\n");
        } else {
            printf("✓ Read %zd bytes successfully\n", num_read_bytes);
            printf("\n============================================================\n");
            printf("📄 NỘI DUNG FILE HOÀN CHỈNH:\n");
            printf("============================================================\n");
            printf("%s", buf);
            printf("============================================================\n");
        }
        
        close(fd);
        free(buf);
        
        read_done = 1;  // Đánh dấu đã đọc xong
        pthread_cond_signal(&cond_input);  // Báo cho thread 1 tiếp tục chu kỳ mới
        
        pthread_mutex_unlock(&lock);
        
        printf("\n✅ Chu kỳ %d hoàn thành! Chuẩn bị chu kỳ tiếp theo...\n", cycle_count);
        
        // Thêm delay nhỏ
        usleep(100000); // 0.1 giây
    }
    
    pthread_exit(NULL);
}

// Signal handler để cleanup khi nhận Ctrl+C
void cleanup_handler(int sig) {
    printf("\n🛑 Nhận tín hiệu dừng (%d). Đang cleanup...\n", sig);
    
    // Cancel tất cả threads
    pthread_cancel(thread_id1);
    pthread_cancel(thread_id2); 
    pthread_cancel(thread_id3);
    
    // Cleanup resources
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond_input);
    pthread_cond_destroy(&cond_write);
    pthread_cond_destroy(&cond_read);
    
    printf("✅ Cleanup hoàn tất. Chương trình kết thúc.\n");
    exit(0);
}

int main(int argc, char* argv[]){ 
    int ret;
    
    // Đăng ký signal handler
    signal(SIGINT, cleanup_handler);  // Ctrl+C
    signal(SIGTERM, cleanup_handler); // Kill command
    
    printf("🚀 CHƯƠNG TRÌNH QUẢN LÝ THÔNG TIN SINH VIÊN (VÔ HẠN)\n");
    printf("============================================================\n");
    printf("Chương trình sử dụng 3 thread chạy vô hạn:\n");
    printf("- Thread 1: Nhập thông tin sinh viên\n");
    printf("- Thread 2: Ghi thông tin vào file\n");
    printf("- Thread 3: Đọc và hiển thị toàn bộ file\n");
    printf("- Sau mỗi chu kỳ, thread 1 sẽ yêu cầu nhập tiếp\n\n");
    printf("⚠️  Nhấn Ctrl+C để dừng chương trình\n");
    printf("============================================================\n");
    
    // Tạo file trống ban đầu
    fd = open("thongtinsinhvien.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd != -1) {
        write(fd, "=== DANH SÁCH SINH VIÊN ===\n", 28);
        close(fd);
    }
    
    // Tạo các thread
    if((ret = pthread_create(&thread_id1, NULL, &thr_handle1, NULL))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if((ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    if((ret = pthread_create(&thread_id3, NULL, &thr_handle3, NULL))) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    // Chờ tất cả thread (sẽ chạy vô hạn cho đến khi nhận signal)
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);
    
    return 0;
}