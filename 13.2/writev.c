#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>

int main(int argc, char* argv[]){
    int str_len;
    struct iovec vec[2];
    char buf1[] = "ABCDEFG";
    char buf2[] = "1234567\n";
    vec[0].iov_base = buf1;
    vec[0].iov_len = strlen(buf1);
    printf("buf1 len: %lu \n", strlen(buf1));
    vec[1].iov_base = buf2;
    vec[1].iov_len = strlen(buf2);
    printf("buf2 len: %lu \n", strlen(buf2));
    str_len = writev(1, vec, 2);
    printf("str_len: %d \n", str_len);
    return 0;
}