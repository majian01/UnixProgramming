#include <stdio.h>
#include <stdlib.h>

static void f1(void)
{
    puts("f1 func is working.\n");
}

static void f2(void)
{
    puts("f2 func is working.\n");
}

static void f3(void)
{
    puts("f3 func is working.\n");
}

int main(int argc, char const *argv[])
{
    puts("begin\n");

    atexit(f1);
    atexit(f2);
    atexit(f3);

    puts("End.\n");
    // printf("end.\n");
    return 0;
}
