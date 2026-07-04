#include <stdio.h>
#include <fcntl.h>

int main(){
    FILE* fp;
    int fd = open("/root/TCP-IP/build/bin/15.1/data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("open");
        return 1;
    }
    fp = fdopen(fd, "w");
    fputs("Hello, World!\n", fp);
    fclose(fp);
    return 0;
}