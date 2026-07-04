#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// 使用标准 I/O 来实现 TCP 客户端
#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    int idx = 0;
    int str_len = 0, read_len = 0;
    FILE *readfp, *writefp;
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==-1){
        perror("connect() error");
    }
    else{
        puts("connected......");
    }
    readfp = fdopen(sock, "r");
    writefp = fdopen(dup(sock), "w");
    while(1){
        fputs("input message(Q or q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "Q\n") || !strcmp(message, "q\n")){
            shutdown(writefp, SHUT_WR);
            fclose(writefp);
            break;
        }
        fputs(message, writefp);
        fflush(writefp);
        fgets(message, BUF_SIZE, readfp);
        printf("Message from server : %s \n", message);
    }
    fclose(readfp);
    close(sock);
    return 0;
}