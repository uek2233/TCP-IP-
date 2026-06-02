#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define DATA_SIZE sizeof(int)
void error_handing(char *message);
int calulate(int opnum, int* opdata, char op);

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int i, j, recv_len, recv_cnt;
    int opnd_cnt;
    int res;
    char message[BUF_SIZE];
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
    for(i=0;i<5;i++){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1){
            error_handing("accept() error");
        }
        else{
            printf("connect client %d \n", i+1);
        }
        read(clnt_sock, &opnd_cnt, 1);
        recv_len = 0;
        while((opnd_cnt*DATA_SIZE+1) > recv_len){
            recv_cnt = read(clnt_sock, &message[recv_len], BUF_SIZE-1);
            recv_len += recv_cnt;
        }
        for(j=0;j<recv_len;j++){
            printf("%02x ", message[j]);
        }
        printf("\n");        
        res = calulate(opnd_cnt, (int*)message, message[recv_len-1]);
        write(clnt_sock, &res, sizeof(res));
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}

int calulate(int opnum, int* opdata, char op){
    int res = opdata[0];
    int i;
    switch(op){
        case '+':
            for(i=1;i<opnum;i++){
                res += opdata[i];
            }
            break;
        case '-':
            for(i=1;i<opnum;i++){
                res -= opdata[i];
            }
            break; 
        case '*':
            for(i=1;i<opnum;i++){
                res *= opdata[i];
            }
            break;        
    }
    return res;
}
 void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
 }