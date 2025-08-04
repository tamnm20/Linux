#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

#define THRESHOLD 5

pthread_t thread_id1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;



int counter; //shared variable/shared resources/global variable

typedef struct {
    char name[30];
    char msg[30];
} thr_data_t;

static void *thr_handle1(void *args){
    //pthread_t tid = pthread_self();
    thr_data_t *data = (thr_data_t *) args;
    //sleep(1);
    pthread_mutex_lock(&lock);
    // critical section
    printf("hello %s!\n",data->name);
    while(counter < THRESHOLD){
        counter ++;
        printf("Counter %d\n",counter);
        sleep(1);
    }
    printf("thread1 handler, counter: %d\n", counter);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL); //exit
}

int main(int argc, char* argv[]){ /* Cấp phát stack frame cho hàm main() */
    /* code */
    int ret;
    thr_data_t data ={0};

    strncpy(data.name, "QuangThaoPitor", sizeof(data.name));
    strncpy(data.msg, "KMA thread programming\n", sizeof(data.msg));

    if(ret = pthread_create(&thread_id1, NULL, &thr_handle1, &data)){
        printf("pthread_create() error number=%d\n",ret);
        return -1;
    }

    while(1){
        if(counter == THRESHOLD){
            printf("OK counter = %d\n", counter);
            break;
        }
    }
    //sleep(2);

    // if(ret = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)){
    //     printf("pthread_create() error number=%d\n",ret);
    //     return -1;
    // }
    // //while(1);
    // sleep(5);

    pthread_join(thread_id1, NULL);
    //pthread_join(thread_id2, NULL);
    //printf("thread_id2 termination\n");
    return 0;
}