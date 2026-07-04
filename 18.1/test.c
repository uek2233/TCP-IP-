#include <stdio.h>

int main(){
    int i, clnt_sock = 5;
    int clnt_cnt = 4;
    int clnt_socks[4] = {3, 4, 5, 6};
    for(i=0;i<clnt_cnt;i++){
        if(clnt_socks[i] == clnt_sock){
            while(i<clnt_cnt-1){
                printf("%d\n", i);
                clnt_socks[i] = clnt_socks[i+1];
                i++;
            }
            break;
        }
    }
    clnt_socks[clnt_cnt-1] = 0;
    printf("clnt_socks: ");
    for(i=0;i<clnt_cnt;i++){
        printf("%d ", clnt_socks[i]);
    }
    printf("\n");
    return 0;
}