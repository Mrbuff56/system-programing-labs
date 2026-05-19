#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
    pid_t pid;
    int i;
    int num_children = 4;
    
    printf("Родительский процесс начался (PID: %d, PPID: %d)\n", 
           getpid(), getppid());
    
    for (i = 0; i < num_children; i++) {
        pid = fork();
        
        if (pid < 0) {
            perror("Ошибка при вызове fork()");
            exit(-1);
        }
        else if (pid == 0) {
            int sleep_time = i + 1;  
            int child_num = i + 1;
            
            printf("Дочерний процесс %d создан (PID: %d, PPID: %d)\n",
                   child_num, getpid(), getppid());
            
            printf("Процесс %d засыпает на %d секунд...\n", child_num, sleep_time);
            sleep(sleep_time);
            
            printf("Процесс %d проснулся\n", child_num);
            
            exit(child_num);  
        }
    }
    
    printf("\nРодительский процесс (PID: %d) ожидает завершения дочерних...\n", getpid());
    
    int status;
    pid_t child_pid;
    int finished_children = 0;
    
    while (finished_children < num_children) {
        child_pid = wait(&status);
        
        if (child_pid == -1) {
            if (errno == ECHILD) {
                break;
            } else {
                perror("Ошибка при вызове wait()");
                exit(-1);
            }
        }
        
        finished_children++;
        
        if (WIFEXITED(status)) {
            printf("Дочерний процесс с PID %d завершился с кодом: %d\n",
                   child_pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Дочерний процесс с PID %d завершился по сигналу: %d\n",
                   child_pid, WTERMSIG(status));
        }
        else {
            printf("Дочерний процесс с PID %d завершился непонятным образом\n",
                   child_pid);
        }
    }
    
    printf("Все дочерние процессы завершены. Родительский процесс завершает работу.\n");
    return 0;

}
