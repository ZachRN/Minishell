#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_pwd(void)
{
    char *path;

    path = getcwd(NULL, 0);
    if (!path)
        return (-1);
    printf("%s", path);
    if (path)
        free(path);
    return (1);
}