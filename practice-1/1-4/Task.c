#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void execute_and_save(FILE *fp, const char *command) {
    char buffer[BUFFER_SIZE];
    FILE *pipe = popen(command, "r");
    
    if (!pipe) {
        fprintf(fp, "Ошибка выполнения команды: %s\n", command);
        return;
    }
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        fputs(buffer, fp);
    }
    
    pclose(pipe);
}

int main() {
    FILE *fp;
    
    fp = fopen("analysis.txt", "w");
    if (!fp) {
        printf("Ошибка открытия файла!\n");
        return -1;
    }

    fprintf(fp, "Процессы systemd:\n");
    execute_and_save(fp, "ps aux | grep systemd");
    fprintf(fp, "\n");
    
    printf("Введите PID процесса systemd: ");
    char pid[20];
    scanf("%s", pid);
    fprintf(fp, "Анализируем процесс с PID: %s\n", pid);
    
    fprintf(fp, "\nДерево процессов для PID %s:\n", pid);
    char cmd[100];
    sprintf(cmd, "pstree -p %s", pid);
    execute_and_save(fp, cmd);
    
    fprintf(fp, "\nСодержимое /proc/%s/cmdline:\n", pid);
    sprintf(cmd, "cat /proc/%s/cmdline", pid);
    execute_and_save(fp, cmd);
    fprintf(fp, "\n");
    
    fprintf(fp, "\nСтатус процесса :\n");
    sprintf(cmd, "head -10 /proc/%s/status", pid);
    execute_and_save(fp, cmd);
    
    fclose(fp);
    
    printf("\nРезультаты сохранены в analysis.txt\n");
    
    printf("\nСодержимое analysis.txt:\n");
    system("cat analysis.txt");
    
    return 0;
}