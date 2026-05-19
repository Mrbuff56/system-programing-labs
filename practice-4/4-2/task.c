#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    const char *filename;
    char filename_buf[PATH_MAX] = {0};
    
    if (argc == 2) {
        filename = argv[1];
    } else {
        printf("Введите название файла: ");
        if (fgets(filename_buf, sizeof(filename_buf), stdin) == NULL) {
            fprintf(stderr, "Ошибка чтения имени файла\n");
            return 1;
        }
        size_t len = strlen(filename_buf);
        if (len > 0 && filename_buf[len - 1] == '\n') {
            filename_buf[len - 1] = '\0';
        }
        if (strlen(filename_buf) == 0) {
            fprintf(stderr, "Ошибка: имя файла не введено\n");
            return 1;
        }
        filename = filename_buf;
    }
    
    int fd = -1;
    struct stat st;
    int *data = NULL;
    size_t num_elements = 0;
    long long sum = 0;
    double average = 0.0;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s': %s\n", 
                filename, strerror(errno));
        return 1;
    }
    
    if (fstat(fd, &st) == -1) {
        fprintf(stderr, "Ошибка: не удалось получить информацию о файле '%s': %s\n", 
                filename, strerror(errno));
        close(fd);
        return 1;
    }
    
    if (st.st_size == 0) {
        fprintf(stderr, "Ошибка: файл '%s' пуст\n", filename);
        close(fd);
        return 1;
    }
    
    if (st.st_size % sizeof(int) != 0) {
        fprintf(stderr, "Предупреждение: размер файла (%lld) не кратен размеру int (%lu)\n", 
                (long long)st.st_size, sizeof(int));
    }
    
    num_elements = st.st_size / sizeof(int);
    printf("Файл '%s' содержит %zu целых чисел (%lld байт)\n", 
           filename, num_elements, (long long)st.st_size);
    
    data = (int*)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        fprintf(stderr, "Ошибка: не удалось отобразить файл в память: %s\n", 
                strerror(errno));
        close(fd);
        return 1;
    }
    
    close(fd);
    fd = -1;
    
    printf("Числа в файле:\n");
    
    for (size_t i = 0; i < num_elements; i++) {
        printf("  [%zu] = %d\n", i, data[i]);

        if (i > 0) {
            if ((data[i] > 0 && sum > LLONG_MAX - (long long)data[i]) ||
                (data[i] < 0 && sum < LLONG_MIN - (long long)data[i])) {
                fprintf(stderr, "Предупреждение: возможное переполнение суммы\n");
            }
        }
        
        sum += data[i];
    }
    
    if (num_elements > 0) {
        average = (double)sum / num_elements;
    }
    
    printf("\nРезультаты:\n");
    printf("  Количество элементов: %zu\n", num_elements);
    printf("  Среднее значение: %.2f\n", average);
    
    if (munmap(data, st.st_size) == -1) {
        fprintf(stderr, "Ошибка: не удалось освободить отображение памяти: %s\n", 
                strerror(errno));
        return 1;
    }
    
    return 0;
}