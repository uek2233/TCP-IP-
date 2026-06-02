#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    pid_t pid;
    pid = fork();
    if(pid == 0){
        printf("Hi, I am a child process.\n");
        printf("End child process.\n");

    }
    else{
        printf("Hi, I am a parent process.\n");
        sleep(30);
        printf("End parent process.\n");
    }
    return 0;
}