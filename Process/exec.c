#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    puts("begin.\n");
    fflush(NULL);

    execl("/bin/date", "date","+%s", NULL);
    perror("execl error.");
    exit(1);

    puts("end.\n");
    
    return 0;
}
