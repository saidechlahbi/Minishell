#include "../includes/minishell.h"
#include <fcntl.h>

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
		return (1);
	return (0);
}
char    *randomize()
{
    char buffer[200];
    char str[20];
    int i = 0;
    int j = 0;

    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1)
        return ;
    read(fd,buffer,200);
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

int main()
{
    randomize();
}
