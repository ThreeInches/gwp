#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE* file = NULL;
    file = fopen("./test.txt", "a+");
    if(file == NULL)
    {
        perror("open file failed");
        return -1;
    }
    fseek(file, 0, SEEK_END);
    char buf[] = "It's a sunny day\n";
    int ret = fwrite(buf, strlen(buf), 1, file);
    if(ret == 0)
    {
        perror("fwrite filed");
        return -1;
    }
    fseek(file, 0, SEEK_SET);
    char tmp[1024] = { 0 };
    ret = fread(tmp, 1023, 1, file);
    printf("ret :%d-[%s]\n", ret, tmp);
    fclose(file);
    return 0;
}
