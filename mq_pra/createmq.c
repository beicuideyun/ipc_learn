#include <stdio.h>  //perror()
#include <mqueue.h> //mq_open()
#define FILE_MODE (S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH) //0644
int main(){
    struct mq_attr attr;
    attr.mq_maxmsg = 100;
    attr.mq_msgsize = 100;
    mqd_t mqd = mq_open("/tmp.test", O_CREAT,FILE_MODE, &attr);
    if(-1 == mqd){
        perror("mq_open error");
        return 1;
    } 
}
