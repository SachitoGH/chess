#include "chess.h"

int	disambiguate(char *san, char **move, char piece, t_move tmp, int takes, int len)
{
	int	i;
	int	j;

	if ((piece == 'p' && len < 3 + takes) || (len < 4 + takes)) 
		return (1);
	if (san[1] >= 'a' && san[1] <= 'h')
	{
		tmp.from[1] = san[1] - 'a';
		j = tmp.from[1];
		for (i = 0; i < 8; i++)
		{
			tmp.from[0] = i;
			if (board[i][j].piece.name == piece && !is_legal_move(tmp))
			{
				if ((!takes && !board[tmp.to[0]][tmp.to[1]].piece.name) || (takes && board[tmp.to[0]][tmp.to[1]].piece.name && board[tmp.to[0]][tmp.to[1]].piece.team != player))
				{	
					(*move)[0] = san[1];
					(*move)[1] = '8' - i;
					return (0);
				}
			}
		}
	}
	else if (san[1] >= '1' && san[1] <= '8')
	{
		tmp.from[0] = 8 - (san[1] - '1' + 1);
		i = tmp.from[0];
		for (j = 0; j < 8; j++)
		{
			tmp.from[1] = j;
			if (board[i][j].piece.team == player && board[i][j].piece.name == piece && !is_legal_move(tmp))
			{
				if ((!takes && !board[tmp.to[0]][tmp.to[1]].piece.name) || (takes && board[tmp.to[0]][tmp.to[1]].piece.name && board[tmp.to[0]][tmp.to[1]].piece.team != player))
				{	
					(*move)[0] = 'a' + j;
					(*move)[1] = san[1];
					return (0);
				}
			}
		}
	}
	return (1);
}



char	*san_to_coord(char *san)
{
	t_move	tmp;
    char	piece;
    char    *move;
	int		takes;
    int     len;
	int		found;
	int		i;
	int		j;

	takes = 0;
	move = malloc(sizeof(char) * 5);
    if (!move)
        return (0);
    if (!strcmp(san, "O-O") || !strcmp(san, "O-O-O"))
	{
		castling(san, &move);
		return (move);
	}
	len = 0;
	while (san[len])
	{
		if (san[len] == 'x')
			takes++;
		len++;
	}
    move[2] = san[len - 2];
    move[3] = san[len - 1];
    move[4] = '\0';
	if (is_piece(san[0]))
		piece = san[0] += 32;
	else
		piece = 'p';
	tmp.to[1] = move[2] - 'a';
	tmp.to[0] = move[3] - '1';
	tmp.to[0] += 7 - (tmp.to[0] * 2);
	found = 0;
	i = 0;
	while (i < 8)
	{
		tmp.from[0] = i;
		j = 0;
		while (j < 8)
		{
			tmp.from[1] = j;
			if (board[i][j].piece.team == player && board[i][j].piece.name == piece && !is_legal_move(tmp))
			{
				if (found == 0 && ((!takes && !board[tmp.to[0]][tmp.to[1]].piece.name) || (takes && board[tmp.to[0]][tmp.to[1]].piece.name && board[tmp.to[0]][tmp.to[1]].piece.team != player)))
				{
					move[0] = 'a' + j;
					move[1] = '8' - i;
					found++;
				}
				else if (found && ((!takes && !board[tmp.to[0]][tmp.to[1]].piece.name) || (takes && board[tmp.to[0]][tmp.to[1]].piece.name && board[tmp.to[0]][tmp.to[1]].piece.team != player)))
				{
					if (disambiguate(san, &move, piece, tmp, takes, len))
					{
						printf("%sAMBIGUATE MOVE%s\n", color("red"), color(0));
						free(move);
						return (0);
					}
				}
			}
			j++;
		}
		i++;
	}
	if (found)
		return (move);
	free(move);
	return (0);
}
int	str_to_move(char *move_str, t_move *move)
{
	move_str = san_to_coord(move_str);
	if (!move_str)
		return (1);
	convert_coord(move_str, move);
	free(move_str);
	return (0);
}

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