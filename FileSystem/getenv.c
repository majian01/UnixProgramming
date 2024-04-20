/**
 * @file getenv.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    puts(getenv("PATH"));
    return 0;
}

