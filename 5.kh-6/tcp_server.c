#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]){
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size;
    char recv_msg[BUF_SIZE] = {0};
    char* send_msg = NULL;
    int name_len, file_size, read_cnt;
    if(argc != 2){
        printf("usage: %s <port>\n", argv[0]);
    }
    server_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(server_sock == -1){
        perror("socket error\n");
        exit(1);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = ntohs(atoi(argv[1]));
    if(bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("bind error\n");
        exit(1);        
    }
    if(listen(server_sock, 5) == -1){
        perror("listen error\n");
        exit(1); 
    }
    client_addr_size = sizeof(client_addr);
    printf("等待客户端连接\n");
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if(client_sock == -1){
        perror("accept error\n");
        exit(1);         
    }
    printf("客户端输入\n");
    // 接受文件名长度
    recv(client_sock, &name_len, 4, 0);
    printf("文件名长度: %d\n", name_len);
    // 接受文件名
    recv(client_sock, recv_msg, name_len, MSG_WAITALL);
    // int i = 0;
    // for(i=0;i<name_len;i++){
    //     printf("%02x ", recv_msg[i]);
    // }
    // printf("\n");
    recv_msg[name_len] = '\0';
    printf("客户端索要文件: %s\n", recv_msg);
    // 打开文件
    FILE* fp = fopen(recv_msg, "rb");
    // 发送文件大小
    if(fp < 0 ){
        printf("文件不存在\n");
        file_size = 0;
        goto end;
    }
    else{
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
    }
    printf("客户端索要文件大小: %d\n", file_size);
    send(client_sock, &file_size, 4, 0);
    // 发送文件
    send_msg = (char*)malloc(sizeof(char)*file_size);
    if(send_msg == NULL){
        perror("malloc error\n");
        exit(1);
    }
    while(read_cnt = fread(send_msg, 1, file_size, fp) > 0){
        send(client_sock, send_msg, read_cnt, 0);
    }
    free(send_msg);
    fclose(fp);
end:
    close(client_sock);
    close(server_sock);
    return 0;
}

