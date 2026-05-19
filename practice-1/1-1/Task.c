#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd1, fd2;
    ssize_t bytes_written,bytes_read;
    char buffer[4096];
    int startWordCount=25;
    int wordCount=0;
    size_t pos = 0;
    bool isWord=false;
    char count_str[64];
    int count_len;
    for (int i = 0; i < startWordCount; i++) {
        int written = snprintf(buffer + pos, sizeof(buffer) - pos, "word%d\n", i);
        if (written < 0 || (size_t)written >= sizeof(buffer) - pos) {
            fprintf(stderr, "Ошибка: буфер переполнен\n");
            return -1;
        }
        pos += written;
    }

    fd1 = open("words.txt", O_RDWR|O_CREAT);
    if (fd1 == -1) {
        perror("Ошибка создания words.txt");
        return -1;
    }
    bytes_written = write(fd1, buffer, strlen(buffer));
    if (bytes_written == -1) {
        perror("Ошибка записи в words.txt");
        close(fd1);
        return -1;
    }
    close(fd1);

    fd2 = open("words.txt", O_RDONLY);
    if (fd2 == -1) {
        perror("Ошибка открытия words.txt");
        return -1;
    }
      while ((bytes_read = read(fd2, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == ' ' || buffer[i] == '\n') {
                if (isWord) {
                    wordCount++;
                    isWord = false;
                }
            } else {
                isWord = true;
            }
        }
    }
    if (isWord) {
        wordCount++;
    }
    if (bytes_read == -1) {
        perror("Ошибка чтения words.txt");
        close(fd2);
        return -1;
    }
    close(fd2);

    fd1 = open("wordcount.txt",  O_RDWR|O_CREAT);
    if (fd1 == -1) {
        perror("Ошибка создания wordcount.txt");
        return 1;
    }

    count_len = snprintf(count_str, sizeof(count_str), "Количество слов: %d\n", wordCount);
    
    bytes_written = write(fd1, count_str, count_len);
    if (bytes_written == -1) {
        perror("Ошибка записи в words.txt");
        close(fd1);
        return -1;
    }
    close(fd1);

    return 0;
}
