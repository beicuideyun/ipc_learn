#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

void client(int readfd, int writefd);
void server(int readfd, int writefd);

int main(int argc,char **argv)
{
    int pipe1[2], pipe2[2];
    int childpid;

    pipe(pipe1);
    pipe(pipe2);

    if( (childpid = fork()) == 0)  //child
    {
        close(pipe1[1]);
        close(pipe2[0]);

        server(pipe1[0],pipe2[1]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[1]);

    client(pipe2[0],pipe1[1]);

    waitpid(childpid, NULL, 0);
    exit(0);
}

void server(int readfd, int writefd)
{
    int fd;
    size_t n;
    char buff[4097];

    if( (n = read(readfd, buff, 4096)) == 0)
    {
        perror("read file error \n");
        return;
    }

    buff[n] = '\0';
    printf("the server get filename from client:%s\n", buff);

    if( (fd = open(buff, O_RDONLY)) < 0)
    {
        perror("the file file can't open file\n");  
        write(writefd, buff , n);
    }
    else
    {
        while( (n = read(fd, buff, 4096)) > 0)
        {
            printf("the server read file:%s\n", buff);
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
