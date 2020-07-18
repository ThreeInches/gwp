#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char buf[] = "ls   -a    -l   ";
    char* ptr = buf;
    char* new_argv[32] = { NULL };
    int new_argc = 0;
    while(*ptr != '\0')
    {
        if(*ptr != ' ')
        {
            new_argv[new_argc] = ptr;
            new_argc++;
            while(*ptr != ' ')
            {
                ptr++;
            }
            *ptr = '\0';
        }
        ptr++;
    }
    int i = 0;
    for(; i < new_argc; i++)
    {
        printf("new_argv[%d] = %s\n", i, new_argv[i]);
    }
    return 0;
}
