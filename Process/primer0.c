#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#define LEFT  30000000
#define RIGHT 30000200


int main(int argc, char const *argv[])
{
    for (int32_t i = LEFT; i < RIGHT; i++)
    {
        int mark = 1;
        for (int32_t j = 2; j < i/2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark == 1)
        {
            printf("%d is a primer\n", i);
        }
    }
    
    return 0;
}
