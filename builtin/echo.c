#include "../includes/minishell.h"
#include <string.h>

void    ft_echo(char **args)
{
    int i;
    int j;
    int n;

    i = 1;
    n = 0;
    while (args[i])
    {
        j = 0;
        if (args[i][j] == '-')
            j++;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j])
            break; 
        i++;
        n = 1;
    }
    while(args[i])
    {
        ft_putstr_fd("%s", args[i]);
        if(args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (!n)
        write(1, "\n", 1);
}

