#include <stdio.h>
#include <pthread.h>

long long product = 1;

pthread_mutex_t mutex;

void* multiply(void* arg) {
    int value = *((int*)arg);
    
    pthread_mutex_lock(&mutex);
    
    printf("Поток для значения %d: product = ", value);
    product *= value;
    printf("%lld\n", product);
    
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int values[5] = {1, 2, 3, 4, 5};
    
    pthread_mutex_init(&mutex, NULL);
    
    printf("Начальное значение product = %lld\n\n", product);
    
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, multiply, &values[i]);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    
    printf("\nPезультат: product = %lld\n", product);
    return 0;
}