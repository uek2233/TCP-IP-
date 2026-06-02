#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define STRING_LEN 4
void error_handing(char *message);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr;
    char send_msg[BUF_SIZE];
    char recv_msg[BUF_SIZE];
    int i, j, char_len;
    int recv_len, recv_cnt, tmp;
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
    for(i=0;i<3;i++){
        memset(send_msg, 0x00, BUF_SIZE);
        memset(recv_msg, 0x00, BUF_SIZE);
        printf("Input string length: ");
        scanf("%d", &char_len);
        fgetc(stdin);
        if(char_len == 0){
            break;
        }
        memcpy(send_msg, &char_len, STRING_LEN);
        fputs("Input string: ", stdout);
        fgets(&send_msg[4], BUF_SIZE-STRING_LEN, stdin);
        send_msg[STRING_LEN+char_len] = '\0';
        for(j=0;j<strlen(&send_msg[STRING_LEN])+STRING_LEN;j++){
            printf("%02x ", send_msg[j]);
        }
        printf("\n");
        write(sock, send_msg, strlen(&send_msg[STRING_LEN])+STRING_LEN);
        read(sock, &recv_len, STRING_LEN);
        recv_cnt = 0;
        while(recv_len > recv_cnt){
            tmp = read(sock, recv_msg, recv_len);
            if(tmp == -1){
                error_handing("read() error");
            }
            recv_cnt += tmp;
        }
        recv_msg[recv_len] = 0;
        printf("Received message from server : %s \n", &send_msg[STRING_LEN]);
    }
    close(sock);
    return 0;
}

void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}