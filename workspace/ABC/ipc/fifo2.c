#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    mkfifo("tp", 0644);
    
    int infd;
    infd = open("abc", O_RDONLY);
    if(infd < 0)
    {
        perror("open error\n");
        return -1;
    }

    int outfd;
    outfd = open("tp", O_WRONLY);
    if(outfd < 0)
    {
        perror("open error\n");
        return -1;
    }

    int ret;
    char buf[1024];
    while((ret = read(infd, buf, 1024)) > 0)
    {
        write(outfd, buf, ret);
        
    }
    close(infd);
    close(outfd);
    return 0;
}
