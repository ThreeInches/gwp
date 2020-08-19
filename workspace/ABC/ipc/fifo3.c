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
    int outfd;
    outfd = open("abc.back", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if(outfd < 0)
    {
        perror("open error\n");
        return -1;
    }

    int infd;
    infd = open("tp", O_RDONLY);
    if(infd < 0)
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
    unlink("tp");
    return 0;
}
