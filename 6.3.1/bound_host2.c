#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int sock;
    char msg1[BUF_SIZE] = "Hi!";
    char msg2[BUF_SIZE] = "I'm another UDP host!";
    char msg3[BUF_SIZE] = "Nice to meet you";
    int str_len;
    socklen_t addr_size;
    struct sockaddr_in serv_addr, from_addr;
    
    if(argc!=3){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        perror("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    sendto(sock, msg1, strlen(msg1), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg2, strlen(msg2), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, msg3, strlen(msg3), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    close(sock);
    return 0;
}