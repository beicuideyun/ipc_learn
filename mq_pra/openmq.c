#include <stdio.h> //perror()
#include <mqueue.h> //mq_open()
int main(){
    mqd_t mqd = mq_open("/tmp.test", O_RDONLY);
    if(-1 == mqd){
        perror("mq_open error");
        return 1;
    }
    return 0;
}
