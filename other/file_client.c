#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 8192

static int recv_all(int fd, void *buf, size_t len) {
    size_t total = 0;
    while (total < len) {
        ssize_t n = recv(fd, (char *)buf + total, len - total, 0);
        if (n <= 0) return -1;
        total += n;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_ip> <filename>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(8080)
    };
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    // 发送文件名（带换行作为结束标志）
    send(sock, argv[2], strlen(argv[2]), 0);
    send(sock, "\n", 1, 0);

    // 先收 8 字节：文件大小
    int64_t file_size;
    if (recv_all(sock, &file_size, sizeof(file_size)) < 0) {
        fprintf(stderr, "Failed to receive file size\n");
        close(sock);
        return 1;
    }
    file_size = be64toh(file_size);

    if (file_size < 0) {
        fprintf(stderr, "Server does not have: '%s'\n", argv[2]);
        close(sock);
        return 1;
    }

    printf("Receiving %ld bytes...\n", file_size);

    // 客户端保存到本地文件（二进制写），只取文件名去掉路径
    const char *basename = strrchr(argv[2], '/');
    basename = basename ? basename + 1 : argv[2];
    char save_path[320];
    snprintf(save_path, sizeof(save_path), "received_%s", basename);
    FILE *fp = fopen(save_path, "wb");
    if (!fp) {
        perror("fopen");
        close(sock);
        return 1;
    }

    char buf[BUF_SIZE];
    int64_t remaining = file_size;
    while (remaining > 0) {
        size_t want = remaining < (int64_t)sizeof(buf) ? (size_t)remaining : sizeof(buf);
        ssize_t n = recv(sock, buf, want, 0);
        if (n <= 0) { perror("recv"); break; }
        fwrite(buf, 1, n, fp);
        remaining -= n;
    }

    fclose(fp);
    close(sock);
    printf("Saved to '%s' (%ld bytes)\n", save_path, file_size - remaining);
    return 0;
}
