#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char* argv[]){
    int tcp_sock, udp_sock;
    int status;
    int sock_type;
    socklen_t optlen;
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    printf("SOCK_STREAM: %d \n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d \n", SOCK_DGRAM);

    status = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
    if(status == -1){
        perror("getsockopt() error\n");
        exit(1);
    }
    printf("SOCK_STREAM: %d \n", sock_type);

    status = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void*)&sock_type, &optlen);
    if(status == -1){
        perror("getsockopt() error\n");
        exit(1);
    }
    printf("SOCK_DGRAM: %d \n", sock_type);
    return 0;
}

