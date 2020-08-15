#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    extern char** environ;
    for(int i = 0; environ[i]; i++)
    {
        printf("env[%d]:%s\n", i, environ[i]);
    }
    return 0;
}
