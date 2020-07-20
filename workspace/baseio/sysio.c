#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    umask(0);
    int fd = -1;
    fd = open("./test2.txt", O_RDWR|O_CREAT, 0777);
    if(fd < 0)
    {
        perror("open error");
        return -1;
    }

    lseek(fd, 0, SEEK_END);
    char* ptr = "I am a student!\n";
    int res = write(fd, ptr, strlen(ptr));
    if(res < 0)
    {
        perror("write error");
        return -1;
    }
    printf("res = %d\n", res);

    lseek(fd, 0, SEEK_SET);
    char buf[1024] = { 0 };
    res = read(fd, buf, 1024);
    if(res < 0)
    {
        perror("read error");
        return -1;
    }
    printf("res:%d--[%s]\n", res, buf);
    return 0;
}
