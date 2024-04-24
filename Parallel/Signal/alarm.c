#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    alarm(3);
    alarm(3);
    alarm(3);
    alarm(10);  //默认执行最后一个
    // getchar();

    while (1)
    {
        // pause();
    }
    
    
    return 0;
}
