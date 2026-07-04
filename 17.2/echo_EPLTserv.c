#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4
#define EPOLL_SIZE 50

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char buf[BUF_SIZE];

    struct epoll_event* ep_events;
    struct epoll_event event;
    int epfd, event_cnt;
    int i, str_len;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        printf("bind() error\n");
        exit(1);
    }
    if(listen(serv_sock, 5) == -1){
        printf("listen() error\n");
        exit(1);
    }

    // 1. 注册 epoll 事件
    epfd = epoll_create(EPOLL_SIZE);

    // 2. 分配 epoll 事件数组
    ep_events = malloc(sizeof(struct epoll_event)* EPOLL_SIZE);
    event.events = EPOLLIN;
    event.data.fd = serv_sock;
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
    
    while(1){
    // 3. 等待事件发生
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
        if(event_cnt == -1){
            printf("epoll_wait() error\n");
            break;          
        }
        printf("return epoll_wait: %d\n", event_cnt);
    // 4. 利用 I/O 分离的思想，连接请求与数据传输请求分离
        for(i=0;i<event_cnt;i++){
    // 5. 如果是连接请求，则注册新的事件
            if(ep_events[i].data.fd == serv_sock){
                clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                printf("connected client: %d\n", clnt_sock);
            }
    // 6. 如果是数据传输请求，则读取数据并回送
            else{
                str_len = read(ep_events[i].data.fd, buf, BUF_SIZE);
    // 7. 如果 str_len == 0，则关闭连接
                if(str_len == 0){
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client: %d\n", ep_events[i].data.fd);
                }
    // 8. 如果 str_len > 0，则回送数据
                else{
                    write(ep_events[i].data.fd, buf, str_len);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}