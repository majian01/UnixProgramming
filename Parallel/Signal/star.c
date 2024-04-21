#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        write(fileno(stdout), "*", 1);
        sleep(1);
    }
    
    return 0;
}
