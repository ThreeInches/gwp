#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    umask(0);
    mkfifo("mypipe", 0644);
    int fd = open("mypipe", O_RDONLY);
    if(fd < 0)
    {
        perror("open, error\n");
        return -1;
    }
    
    char buf[1024];
    while(1)
    {
        buf[0] = 0;
        printf("please wait...\n");
        ssize_t read_size = read(fd, buf, sizeof(buf) - 1);
        if(read_size > 0)
        {
            buf[read_size - 1] = 0;
            printf("client say # %s\n", buf);
        }
        else if(read_size == 0)
        {
            printf("client quit,exit now!\n");
            return -1;
        }
        else 
        {
            perror("read error\n");
            return -1;
        }
    }
    close(fd);
    return 0;
}
