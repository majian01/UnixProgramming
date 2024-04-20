#include <string.h>
#include <stdio.h>

#define STRSIZE 1024

void stringCut(char* string, int head, int tail)
{
    char *head_ptr, *tail_ptr;
    head_ptr = string;
    tail_ptr = string;
    head_ptr += head * sizeof(char);
    tail_ptr += tail * sizeof(char);
    *tail_ptr = '\n';
    puts(head_ptr);
}

void memchr_use()
{
    char str[STRSIZE] = "abcdefg/1/2/3/./5/6";
    const char sep = '/';
    char* ret;
    ret = (char*)memchr(str, sep, sizeof(str));
    if (ret == NULL)
    {
        puts("no found.\n");
    }
    else
    {
        printf("%c 后的字符串是 %s \n, 位置为%ld", sep, ret, ret - str);
    }
}



int main(int argc, char const *argv[])
{
    char input[20] = "sdfasdfas";
    // stringCut(input, 2, 10);
    memchr_use();
    return 0;
}
