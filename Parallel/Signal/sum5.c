#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>


int main(int argc, char const *argv[])
{
    time_t end;
    int64_t count = 0;
    end = time(NULL) + 5;
    while (time(NULL) <= end)
    {
        count++;
    }

    printf("%ld\n", count);
    
    return 0;
}
