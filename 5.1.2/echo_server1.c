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
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    int i, str_len;
    int* int_arr = NULL;
    char message[BUF_SIZE];
    int res;
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
        // write(clnt_sock, message, sizeof(message));
        int idx = 0;
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){
            res = 0;
            for(i=0;i<str_len;i++){
                printf("%02x ", message[i]);
            }
            printf("\n");
            int_arr = (int*)malloc(sizeof(int)*message[0]);
            switch (message[str_len -1]){
                case '+':
                    for(i=0;i<message[0];i++){
                        // memcpy(&int_arr[i], &message[1+DATA_SIZE*i], DATA_SIZE);
                        int_arr[i] = *(int*)(message+1+DATA_SIZE*i);
                        res += int_arr[i];
                    }
                    break;
                case '-':
                    for(i=0;i<message[0];i++){
                        // memcpy(&int_arr[i], &message[1+DATA_SIZE*i], DATA_SIZE);
                        int_arr[i] = *(int*)(message+1+DATA_SIZE*i);
                        if(i == 0){
                            res = int_arr[0];
                        }
                        else{
                            res -= int_arr[i];
                        }
                        
                    }
                    break;
                case '*':
                    res = 1;
                    for(i=0;i<message[0];i++){
                        // memcpy(&int_arr[i], &message[1+DATA_SIZE*i], DATA_SIZE);
                        int_arr[i] = *(int*)(message+1+DATA_SIZE*i);
                        res *= int_arr[i];
                    }
                    break;
            }
            write(clnt_sock, &res, sizeof(res));
        }
        close(clnt_sock);
    }
    close(serv_sock);
    free(int_arr);
    return 0;
}

 void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
 }