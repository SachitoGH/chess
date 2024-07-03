#include "chess.h"

char    *color(char *name)
{
    if (!name)
        return ("\033[0m"); //default color
    if (!strcmp(name, "purple"))
        return ("\033[1;35m");
    if (!strcmp(name, "white"))
        return ("\033[1;37m");
    if (!strcmp(name, "red"))
        return ("\033[1;31m");
    if (!strcmp(name, "yellow"))
        return ("\033[1;33m");
    if (!strcmp(name, "green"))
        return ("\033[1;32m");
    if (!strcmp(name, "cyan"))
        return ("\033[1;36m");
    if (!strcmp(name, "black"))
        return ("\e[1;30m");
    return ("\033[0m");
}
int inside_board(char letter, char number)
{
    if ((letter >= 'a' && letter <= 'h') && (number >= '1' && number <= '8'))
        return (1);
    return (0);
}       

int is_piece(char p)
{
    if (p == 'P' || p == 'R' || p == 'N' || p == 'B' || p == 'Q' || p == 'K')
        return (1);
    return (0);
}       