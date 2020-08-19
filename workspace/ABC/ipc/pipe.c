#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int fds[2];
    char buf[100];
    int len;
    int ret;

    ret = pipe(fds);
    if(ret > 0)
    {
        perror("pipe error\n");
        return -1;
    }
    while(fgets(buf, 100, stdin))
    {
        len = strlen(buf);
        if(write(fds[1], buf, len) != len)
        {
            perror("write pipe error\n");
            return -1;
        }

        memset(buf, 0x00, sizeof(buf));

        if(read(fds[0], buf, 100) == -1)
        {
            perror("read pipe error\n");
            return -1;
        }

        if(write(1, buf, len) != len)
        {
            perror("write stdout error\n");
            return -1;
        }
    }
    return 0;
}
