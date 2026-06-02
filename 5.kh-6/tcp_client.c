#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int sock;
    int file_size, name_len;
    char send_msg[BUF_SIZE];
    char save_path[BUF_SIZE] = "./recv.txt";
    char* recv_msg = NULL;
    struct sockaddr_in serv_addr;
    if(argc != 3){
        printf("uasge: %s <ip> <port>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket error\n");
        exit(1);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = ntohs(atoi(argv[2]));
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        perror("connect error\n");
        exit(1);
    }
    else{
        printf("connected......\n");
    }
    // 获取文件名并发送
    fputs("input file name: ", stdout);
    scanf(" %s", &send_msg[4]);
    name_len = strlen(&send_msg[4]);
    memcpy(send_msg, &name_len, 4);
    send(sock, send_msg, name_len+4, 0);
    int i = 0;
    for(i=0;i<name_len+4;i++){
        printf("%02x ", send_msg[i]);
    }
    printf("\n");

    recv(sock, &file_size, 4, MSG_WAITALL);
    if(file_size == 0){
        printf("file not exit, close connect!!!\n");
        close(sock);
        exit(1);
    }
    else{
        recv_msg = (char*)malloc(sizeof(char)*file_size);
        recv(sock, recv_msg, file_size, MSG_WAITALL);
    }
    FILE* fp = fopen(save_path, "wb");
    if(fp == NULL){
        perror("fopen error\n");
        exit(1);
    }
    fwrite(recv_msg, 1, file_size, fp);
    fclose(fp);
    close(sock);
    free(recv_msg);
    printf("文件接收完成，保存为：%s, 大小为 %d 字节\n", save_path, file_size);
    return 0;
}

