#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define PORT 8080
#define BUF_SIZE 8192

static void send_file(int client_fd, const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        int64_t size = -1;
        send(client_fd, &size, sizeof(size), 0);
        perror("fopen");
        return;
    }

    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    int64_t file_size = ftell(fp);
    rewind(fp);

    // 先发送文件大小（8 字节，网络字节序）
    int64_t size_net = htobe64(file_size);
    send(client_fd, &size_net, sizeof(size_net), 0);

    // 分块发送文件内容
    char buf[BUF_SIZE];
    size_t n;
    int64_t sent = 0;
    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        ssize_t s = send(client_fd, buf, n, 0);
        if (s < 0) { perror("send"); break; }
        sent += s;
    }
    printf("Sent %ld bytes of '%s'\n", sent, filename);
    fclose(fp);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&addr, &addr_len);
        if (client_fd < 0) { perror("accept"); continue; }
        printf("Client connected: %s\n", inet_ntoa(addr.sin_addr));

        // 接收文件名（以 '\n' 或 '\0' 结尾）
        char filename[256] = {0};
        int n = recv(client_fd, filename, sizeof(filename) - 1, 0);
        if (n > 0) {
            filename[strcspn(filename, "\n\r")] = 0;  // 去掉换行符
            printf("Requested: '%s'\n", filename);
            send_file(client_fd, filename);
        }
        close(client_fd);
        printf("Client disconnected.\n\n");
    }
    close(server_fd);
    return 0;
}
