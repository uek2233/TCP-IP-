#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define BUF_SIZE 512

void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (id > 0 && WIFEXITED(status)) {
        printf("Removed proc id: %d \n", id);
        printf("Child send: %d \n", WEXITSTATUS(status));
    }
}

int main(int argc, char* argv[]){
    int fds[2];
    char str[] = "Who are you?";
    char buf[BUF_SIZE] = {0,};
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    if(pipe(fds) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    pid = fork();
    if(pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
    if(pid == 0){
        close(fds[0]);
        write(fds[1], str, sizeof(str));
        close(fds[1]);
        return 0;
    }
    else{
        close(fds[1]);
        read(fds[0], buf, BUF_SIZE);
        printf("Message from child process: %s\n", buf);
        close(fds[0]);
        sleep(3);
    }
    return 0;
}