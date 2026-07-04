#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>


#define NUM_THREAD 100

void* read_t(void* arg);
void* accu_t(void* arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char* argv[]){
    pthread_t id_t1, id_t2;
    sem_init(&sem_one, 0, 0);
    sem_init(&sem_two, 0, 1);

    pthread_create(&id_t1, NULL, read_t, NULL);
    pthread_create(&id_t2, NULL, accu_t, NULL);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);
    
    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void* read_t(void* arg){
    int i;
    for(i=0;i<5;i++){
        printf("Input num: ");
        sem_wait(&sem_two); // accu_t 加完上 num 后才能赋予 num 新的值
        scanf("%d", &num);
        sem_post(&sem_one); // num 有新的值后才能执行 accu_t 
    }
    return NULL;
}

void* accu_t(void* arg){
    int sum = 0, i;
    for(i=0;i<5;i++){
        printf("accu_t: %d\n", i);
        sem_wait(&sem_one);
        sum += num;
        sem_post(&sem_two);
    }
    printf("reslut: %d\n", sum);
    return NULL;
}