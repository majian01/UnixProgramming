#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

int main(int argc, char const *argv[])
{
    char buf[BUFSIZE];
    int line_count = 0;

    if (argc < 3)
    {
        perror("too few args.");
        exit(1);
    }
    
    FILE* src_file = fopen(argv[1], "r");
    FILE* des_file = fopen(argv[2], "w");

    if (src_file==NULL || des_file == NULL)
    {
        perror("file open failed.\n");
        exit(1);
    }

    while (fgets(buf, BUFSIZ, src_file) != NULL)
    {
        line_count++;
        if (line_count != 10)
        {
            fputs(buf, des_file);
        }
    }
    
    fclose(src_file);
    fclose(des_file);

    return 0;
}
