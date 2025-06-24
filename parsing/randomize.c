#include "../includes/minishell.h"

char    *randomize()
{
    char buffer[200];
    char *str;
    int i = 0;
    int j = 0;

    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1)
        return (NULL);
    read(fd,buffer,200);
    str = malloc(20);
    while (j < 19)
    {
        if (i >= 200)
        {
            read(fd,buffer,200);
            i = 0;
        }
        if (ft_isalnum(buffer[i]))
            str[j++] = buffer[i];
        i++;
    }
    str[j] = '\0';    
    close(fd);
	return (str);
}
