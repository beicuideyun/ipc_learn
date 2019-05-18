#include <stdio.h>
#include <mqueue.h>
#define FILE_MODE (S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH)
int main(int argc, char* argv[]){
    mqd_t mqd = mq_open("/tmp.test", O_RDONLY);
    if(-1 == mqd){
        perror("mq_open error");
        return 1;
    }
    char buf[BUFSIZ];
    unsigned int prio;
    if(-1 == mq_receive(mqd, buf, BUFSIZ, &prio)){
        perror("mq_recv error");
        mq_close(mqd);
        return 1;
    }
    printf("msg:%s\nprio:%d\n", buf, prio);
    mq_close(mqd);
    return 0;
}
