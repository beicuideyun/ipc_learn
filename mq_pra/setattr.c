#include <stdio.h>
#include <string.h>
#include <mqueue.h>
int main(){
    mqd_t mqd = mq_open("/tmp.test", O_RDWR);
    if(-1 == mqd){
        perror("mq_open error");
        return 1;
    }
    struct mq_attr new_attr;
    bzero(&new_attr, sizeof(new_attr));

    new_attr.mq_flags = O_NONBLOCK;
    struct mq_attr attr;
    if(-1 == mq_setattr(mqd, &new_attr, &attr)){
        perror("mq_setattr error");
        mq_close(mqd);
        return 1;
    }
    printf("flag:%ld, Max msg:%ld, Max msgsize:%ld,Cur msgnum:%ld\n", attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    mq_close(mqd);
}
