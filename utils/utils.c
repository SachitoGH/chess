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


int	change_player(void)
{
	if (data.player == 'w')
	{
		data.player = 'b';
		return (-1);
	}
	else
		data.player = 'w';
	return (1);
}

void	print_board(void)
{
	int		i;
	int		j;

	i = 0;
	// printf("%s  a b c d e f g h%s\n", color("red"), color(0));
	while (i < 8)
	{
		printf("%s%c%s", color(COORD_COLOR), '8' - i, color(0));
		j = 0;
		while (j < 8)
		{
			if (!board[i][j].piece.name)
			{
				if (board[i][j].square_color == 'w')
					printf("%s .%s", color(WHITE_COLOR), color(0));
				else
					printf("%s .%s", color(BLACK_COLOR), color(0));
			}
			else if (board[i][j].piece.team == data.player && board[i][j].piece.name == 'k' && my_piece_is_attacked(i, j))
				printf("%s %c%s", color("red"), board[i][j].piece.name - 32, color(0));
			else if (board[i][j].piece.team == 'w' && board[i][j].piece.name == 'p')
				printf("%s %c%s", color(WHITE_COLOR), board[i][j].piece.name, color(0));
			else if (board[i][j].piece.team == 'w')
				printf("%s %c%s", color(WHITE_COLOR), board[i][j].piece.name - 32, color(0));
			else if (board[i][j].piece.name == 'p')
				printf("%s %c%s", color(BLACK_COLOR), board[i][j].piece.name, color(0));
			else
				printf("%s %c%s", color(BLACK_COLOR), board[i][j].piece.name - 32, color(0));
			j++;
		}
		// printf("%s %c%s", color("red"), '8' - i, color(0));
		printf("\n");
		i++;
	}
	printf("%s  a b c d e f g h%s\n", color(COORD_COLOR), color(0));
}

int	verif_input(char *move)
{
	int	len;

	len = strlen(move);
	if (move[len - 2] == '=' && is_piece(move[len - 1]))
	{
		data.promote_to = move[len - 1];
		len -= 2;
	}
	if (len > 5)
		return (0);
	if (len == 2 && inside_board(move[0], move[1]))
		return (1);
	if (len == 3 && is_piece(move[0]) && inside_board(move[1], move[2]))
		return (1);
	if (len == 4 && ((is_piece(move[0]) && inside_board(move[2], move[3])) ||
		((move[0] >= 'a' && move[0] <= 'h') && move[1] == 'x' && inside_board(move[2], move[3]))))
		return (1);
	if (len == 5 && is_piece(move[0]) && ((move[1] >= 'a' && move[1] <= 'h') || (move[1] >= '1' && move[1] <= '8')) &&
		move[2] == 'x' && inside_board(move[3], move[4]))
		return (1);
	if (!strcmp(move, "O-O") || !strcmp(move, "O-O-O"))
		return (1);
	return (0);
}

int	reset_en_passant(void)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		data.en_passant[data.player == 'b'][i] = 0;
		i++;
	}
	return (0);
}

int save_data(t_data *tmp, int mode)
{
	if (mode == 0)
	{
		tmp->promote_to = data.promote_to;
		tmp->player = data.player;
		tmp->is_castle = data.is_castle;
		memcpy(tmp->en_passant, data.en_passant, 2 * 8 * sizeof(int));
		memcpy(tmp->can_castle, data.can_castle, 2 * 2 * sizeof(int));
	}
	else if (mode == 1)
	{
		data.promote_to = tmp->promote_to;
		data.player = tmp->player;
		data.is_castle = tmp->is_castle;
		memcpy(data.en_passant, tmp->en_passant, 2 * 8 * sizeof(int));
		memcpy(data.can_castle, tmp->can_castle, 2 * 2 * sizeof(int));
	}
	return (0);
}