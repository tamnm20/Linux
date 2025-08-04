#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

pthread_t thread_id1, thread_id2, thread_id3;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

int counter = 2; //shared variable/shared resources/global variable

typedef struct {
    char name[30];
    char msg[30];
} thr_data_t;

static void *thr_handle1(void *args){
    //pthread_t tid = pthread_self();
    thr_data_t *data = (thr_data_t *) args;
    //sleep(1);
    pthread_mutex_lock(&lock1);
    // critical section
    printf("hello %s!\n",data->name);
    printf("thread1 handler, counter: %d\n", ++counter);
    sleep(5);

    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL); //exit
}

static void *thr_handle2(void* args){
    //pthread_t tid = pthread_self();
    //sleep(1);
    pthread_mutex_lock(&lock1);

    printf("thread2 handler, counter: %d\n", ++counter);

    pthread_mutex_unlock(&lock1);

    pthread_exit(NULL); //exit
}

static void *thr_handle3(void* args){
    // while(1){
    //     printf("thread3 handler\n");
    //     sleep(1);
    // }
    pthread_exit(NULL); //exit
}

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    int ret, counter=0;
    thr_data_t data ={0};

    strncpy(data.name, "QuangThaoPitor", sizeof(data.name));
    strncpy(data.msg, "KMA thread programming\n", sizeof(data.msg));

    if(ret = pthread_create(&thread_id1, NULL, &thr_handle1, &data)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }
    //sleep(2);

    if(ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }
    //while(1);
    sleep(5);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    printf("thread_id2 termination\n");
    return 0;
}