#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int main(int argc, char const *argv[])
{

    for (int i = 0; environ[i] != NULL; i++)
    {
        puts(environ[i]);
    }
    
    return 0;
}
