#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int recv_len;
    int option, optlen;
    char message[BUF_SIZE];
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        perror("socket() error\n");
        exit(1);
    }
    // 设置套接字选项，允许地址重用
    option = TRUE;
    optlen = sizeof(option);
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void*)&option, optlen);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==-1){
        perror("bind() error\n");
        exit(1);
    }
    if(listen(serv_sock, 5)==-1){
        perror("listen() error\n");
        exit(1);
    }
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        perror("accept() error\n");
        exit(1);
    }
    while((recv_len = recv(clnt_sock, message, BUF_SIZE, 0)) != 0){
        send(clnt_sock, message, recv_len, 0);
        if (write(1, message, recv_len) == -1){
            perror("write() error");
        }
    }
    close(clnt_sock);
    close(serv_sock);
    return 0;
}