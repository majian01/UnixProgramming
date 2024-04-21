#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glob.h>
#include <wait.h>
#include <string.h>

#define SEP " \t\n"

struct cmd_st
{
    glob_t glob_res;
};

static void promt(void)
{
    printf("mysh-0.1$ ");
}

static void parse(char* line, struct cmd_st* cmd)
{
    char* tok;
    int i = 0;
    while (1)
    {
        tok = strsep(&line, SEP);
        if (tok == NULL)
        {
            break;
        }

        if (tok[0] == '\0')
        {
            continue;
        }

        glob(tok, GLOB_NOCHECK|GLOB_APPEND*i, NULL, &cmd->glob_res);
        i = 1;  //保证只有第一次才会append
    }
}


int main(int argc, char const *argv[])
{
    char *linebuf = NULL;
    size_t linebuf_size = 0;
    struct cmd_st cmd;
    pid_t pid;
    while (1)
    {
        promt();
        if(getline(&linebuf, &linebuf_size, stdin) < 0)
        {
            break;
        }

        parse(linebuf, &cmd);

        // for (int i = 0; i < cmd.glob_res.gl_pathc; i++)
        // {
        //     printf("%ld", cmd.glob_res.gl_pathc);
        //     puts(cmd.glob_res.gl_pathv[i]);
        // }
        

        if (0)  //外部命令
        {
        
        }
        else
        {
            if((pid = fork()) < 0)
            {
                perror("fork.");
                exit(1);
            }
            if (pid == 0)
            {
                // execvp(cmd.glob_res.gl_pathv[0], cmd.glob_res.gl_pathv);
                execvp(cmd.glob_res.gl_pathv[0], cmd.glob_res.gl_pathv);
                perror("exec()");
                exit(1);
            }
            else
            {
                wait(NULL);
            }
        }
    }
    
    return 0;
}
