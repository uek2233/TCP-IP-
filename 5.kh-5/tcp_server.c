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
    int serv_sock;
    int clnt_sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    int char_len, recv_len, recv_cnt, i, send_len;
    int retry = 0;
    char recv_msg[BUF_SIZE];
    char send_msg[BUF_SIZE];
    if(argc!=2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handing("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==-1){
        error_handing("bind() error");
    }
    if(listen(serv_sock, 5)==-1){
        error_handing("listen() error");
    }
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        error_handing("accept() error");
    }
    else{
        printf("connect client\n");
    }
    while(1){
        printf("Waiting for data......\n");
        recv_cnt = read(clnt_sock, &char_len, STRING_LEN);
        if(recv_cnt < 0 || char_len == 0){
            break;
        }
        recv_len = 0;
        while(recv_len < char_len){
            printf("recv_len:%d\n", recv_len);
            recv_cnt = read(clnt_sock, recv_msg, BUF_SIZE-1);
            if(recv_cnt < 0){
                error_handing("read() error");
            }
            recv_len += recv_cnt;
            if(recv_len == 0){
                retry += 1;
            }
            if(retry >= 3){
                goto err;
            }
        }
        printf("clnt_sock:%d, recv_len:%d\n", char_len, recv_len);
        printf("Received raw data:\n");
        for(i=0;i<char_len;i++){
            printf("%02x ", recv_msg[i]);
        }
        printf("\n");
        if(char_len != recv_len){
            printf("clnt_sock:%d != recv_len:%d\n", char_len, recv_len);
        }
        else{
            recv_msg[recv_len] = 0;
            printf("char_len: %d recv_len: %d message: %s\n", char_len, recv_len, recv_msg);
            sprintf(&send_msg[STRING_LEN], "Received %d bytes\n", recv_len);
            send_len = strlen(&send_msg[STRING_LEN]);
            memcpy(send_msg, &send_len, STRING_LEN);
            printf("send_msg:%s\n", &send_msg[STRING_LEN]);
            write(clnt_sock, send_msg, send_len+STRING_LEN);
        }
    }
err:
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

 void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
 }