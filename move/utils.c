#include "chess.h"

int	convert_coord(char *str1, char *str2, int from[2], int to[2])
{
	from[0] = str1[1] - '1';
	from[1] = str1[0] - 'a';
	to[0] = str2[1] - '1';
	to[1] = str2[0] - 'a';
	from[0] += 7 - (from[0] * 2);
	to[0] += 7 - (to[0] * 2);
	return (0);
}

char    *color(char *name)
{
    if (!name)
        return ("\033[0m"); //default color
    if (!strcmp(name, "purple"))
        return ("\033[0;35m");
    if (!strcmp(name, "red"))
        return ("\033[0;31m");
    return ("\033[0m");
}