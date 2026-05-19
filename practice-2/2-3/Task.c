#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

volatile sig_atomic_t flag = 0;

void handler(int sig) {
    (void)sig; 
    write(STDOUT_FILENO, "Signal received\n", 16);
    flag = 1;
}

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        signal(SIGUSR1, handler);
        printf("Дочерний процесс засыпает\n");
        
        sleep(30);
        
       if (flag) {
            printf("Дочерний процесс получил сигнал\n");
        } else {
            printf("Дочерний процесс проснулся\n");
        }
        
    } else {

        printf("Дочерний процесс создан (PID: %d)\n",pid);
        sleep(5);
        
        printf("Родительский процесс: sending SIGUSR1...\n");
        kill(pid, SIGUSR1);
        
        wait(NULL);
       printf("Дочерний процесс завершился\n");
    }
    
    return 0;
}