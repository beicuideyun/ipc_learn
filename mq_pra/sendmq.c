#include <stdio.h>
#include <mqueue.h>
int main(int argc, char* argv[]){
    mqd_t mqd = mq_open("/tmp.test", O_WRONLY);
    if(-1 == mqd){
        perror("mq_open error");
        return 1;
    }
    const char* msg = "HelloWorldHelloWorldPan";
    if(-1 == mq_send(mqd, msg, sizeof(msg), 1)){
        perror("mq_send error");
        mq_close(mqd);
        return 1;
    }
    mq_close(mqd);
    return 0;
}
