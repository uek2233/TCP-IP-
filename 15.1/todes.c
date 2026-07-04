#include <stdio.h>
#include <fcntl.h>

int main(){
    FILE* fp;
    int fd = open("/root/TCP-IP/build/bin/15.1/data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    printf("first file descriptor: %d\n", fd);
    fp = fdopen(fd, "w");
    printf("TCP/IP SOCKET PROGRAMMING: %p\n", (void*)fp);
    printf("second file descriptor: %d\n", fileno(fp));
    fclose(fp);
    return 0;
}