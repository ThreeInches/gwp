#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    FILE* fp = fopen("write.txt", "w+");
    if(!fp)
    {
        perror("fopen error\n");
    }
    char* msg = "Hello,world!\n";
    int count = 5;
    while(count--)
    {
        fwrite(msg, strlen(msg), 1, fp);
    }
    fclose(fp);
    return 0;
}
