#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#define IPC_KEY 0x12345678

int main()
{
    //1.创建共享内存shmget
    int shm_id = shmget(IPC_KEY, 32, IPC_CREAT|0644);
    if(shm_id < 0)
    {
        perror("shmget error");
        return -1;
    }
    //2.建立映射关系shmat
    void* shm_start = shmat(shm_id, NULL, 0);
    if(shm_start == (void*)-1)
    {
        perror("shmat error");
        return -1;
    }
    //3.进行内存操作
    int i = 0;
    while(1)
    {
        sprintf(shm_start, "%s+%d", "This is a share memory example", i++);
        sleep(1);
    }
    //4.解除映射关系shmdt
    int shm_dt = shmdt(shm_start);
    if(shm_dt == -1)
    {
        perror("shmdt error");
        return -1;
    }
    //5.删除共享内存shm
    shmctl(shm_id, IPC_RMID, NULL);
    return 0;
}
