#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define DATA_SIZE sizeof(int)
void error_handing(char *message);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE] = {0x00};
    int i = 0;
    int str_len = 0, recv_len = 0, recv_cnt = 0;
    int opt_cnt;
    int result;
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        error_handing("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));    
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==-1){
        error_handing("connect() error");
    }
    else{
        puts("connected......");
    }

    fputs("input message(0 to quit)\n", stdout);
    printf("operand count: ");
    scanf("%d", &opt_cnt);
    message[0] = (char)opt_cnt;
    if((message[0] == 0)){
        return 0;
    }
    for(i=0;i<opt_cnt;i++){
        printf("operand %d: ", i+1);
        scanf("%d", (int*)&message[DATA_SIZE*i+1]);
    }
    printf("operand: ");
    scanf(" %c", &message[DATA_SIZE*opt_cnt+1]);
    str_len = write(sock, message, (DATA_SIZE*opt_cnt+2));
    recv_cnt = read(sock, &result, sizeof(result));
    printf("Message len from server : %d\n", recv_cnt);
    printf("result from server : %d\n", result);
    result = 0;
    close(sock);
    return 0;
}

void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}