#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    umask(0);
    int fd = open("test.txt", O_CREAT|O_WRONLY, 0644);
    if(fd < 0)
    {
        perror("open error\n");
        return -1;
    }
    char* msg = "Hello, world\n";
    int count = 5;
    while(count--)
    {
        write(fd, msg, strlen(msg));
    }
    close(fd);
    return 0;
}
