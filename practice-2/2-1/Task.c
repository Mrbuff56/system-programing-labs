#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


long long results[4];
int numbers[4] = {5, 6, 7, 8};

void* calc_fact(void* arg) {
    int index = *(int*)arg;
    int n = numbers[index];
    long long fact = 1;
    
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    
    results[index] = fact;
    printf("Поток %d: вычислил %d! = %lld\n", index, n, fact);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[4];
    int thread_args[4];
    
    printf("4 потока:\n");
    
    for (int i = 0; i < 4; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, calc_fact, &thread_args[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nРезультаты:\n");
    for (int i = 0; i < 4; i++) {
        printf("Факториал %d! = %lld\n", numbers[i], results[i]);
    }
    
    return 0;
}