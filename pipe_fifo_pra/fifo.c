#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>


#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

void client(int readfd, int writefd);
void server(int readfd, int writefd);

int main(int argc, char**argv)
{
    int readfd, writefd;
    pid_t childpid;

    if ((mkfifo(FIFO1, FILE_MODE) < 0) && (errno != EEXIST))  
        printf("can't create %s", FIFO1);  
    if ((mkfifo(FIFO2, FILE_MODE) < 0) && (errno != EEXIST)) {  
        unlink(FIFO1);  
        printf("can't create %s", FIFO2);  
    }  

    if ( (childpid = fork()) == 0) {        /* child */  
        readfd = open(FIFO1, O_RDONLY, 0);  
        writefd = open(FIFO2, O_WRONLY, 0);  

        server(readfd, writefd);  
        exit(0);  
    }  
        /* 4parent */  
    writefd = open(FIFO1, O_WRONLY, 0);  
    readfd = open(FIFO2, O_RDONLY, 0);  

    client(readfd, writefd);  

    waitpid(childpid, NULL, 0);     /* wait for child to terminate */  

    close(readfd);  
    close(writefd);  

    unlink(FIFO1);  
    unlink(FIFO2);  
    exit(0);  
}

void server(int readfd, int writefd)
{
    int fd;
    size_t n;
    char buff[4097];

    if( (n = read(readfd, buff, 4096)) == 0)
    {
        perror("read file error ");
        return;
    }

    buff[n] = '\0';
    printf("the server get filename from client:%s\n", buff);

    if( (fd = open(buff, O_RDONLY)) < 0)
    {
        perror("the file file can't open file");  
        write(writefd, buff , n);
    }
    else
    {
        while( (n = read(fd, buff, 4096)) > 0)
        {
            perror("the server read file:");
            write(writefd, buff , n);
        }

        close(fd);
    }
}

void client(int readfd, int writefd)
{
    size_t len;
    size_t n;

    char buff[4097];
    printf("pls input filename\n");
    fgets(buff, 4096, stdin);

    len = strlen(buff);
    if( buff[len-1] == '\n')
        len--;
    write(writefd, buff, len);

    while( (n = read(readfd, buff ,4096)) > 0)
    {
        printf("the client read message from server:%s\n", buff);
    }
}
