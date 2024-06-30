#include "chess.h"

int	convert_coord(char *move_str, t_move *move)
{
    (*move).from[0] = move_str[1] - '1';
	(*move).from[1] = move_str[0] - 'a';
    (*move).from[0] += 7 - ((*move).from[0] * 2);
    (*move).to[0] = move_str[3] - '1';
	(*move).to[1] = move_str[2] - 'a';
	(*move).to[0] += 7 - ((*move).to[0] * 2);
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