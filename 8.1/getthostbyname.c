#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 128

int main(int argc, char *argv[]) {
    int i;
    struct hostent *host;
    if(argc != 2){
        printf("Usage : %s <hostname>\n", argv[0]);
        exit(1);
    }
    host = gethostbyname(argv[1]);
    if(!host){
        printf("gethostbyname() error\n");
        exit(1);  
    }
    printf("Official name: %s\n", host->h_name);
    for(i=0;host->h_aliases[i];i++){
        printf("Aliases %d: %s \n", i+1, host->h_aliases[i]);
    }
    printf("Address type: %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    for(i=0;host->h_addr_list[i];i++){
        printf("IP addr %d: %s \n", i+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
    }
    return 0;
}

// docker run cloudflare/cloudflared:latest tunnel --no-autoupdate run --token eyJhIjoiMTM3MGU1YzRhZmE0MjQ5MjQ4MWQyZGNlNDE0MmQxNDciLCJ0IjoiMWYzN2JkNTItZTI1Yi00NDFkLWEzOWItMzhiMmM2ZDgxOGU4IiwicyI6Ik9HWXhZbVF5TXpJdE5UazFOaTAwWVRZekxUZzNOV0l0TnpObE1tUTFOV1JsWkRnNCJ9