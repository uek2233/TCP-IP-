#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char* argv[]){
    int sock;
    int snd_buf = 1024*3, recv_buf = 1024*3;
    int status;
    socklen_t len;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    status = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, sizeof(snd_buf));
    if(status == -1){
        perror("setsockopt() error\n");
        exit(1);
    }
    status = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&recv_buf, sizeof(recv_buf));
    if(status == -1){
        perror("setsockopt() error\n");
        exit(1);
    }

    len = sizeof(snd_buf);
    status = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);
    if(status == -1){
        perror("getsockopt() error\n");
        exit(1);
    }
    printf("SO_SNDBUF: %d \n", snd_buf);
    len = sizeof(recv_buf);
    status = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&recv_buf, &len);
    if(status == -1){
        perror("getsockopt() error\n");
        exit(1);
    }
    printf("SO_RCVBUF: %d \n", recv_buf);
    return 0;
}

