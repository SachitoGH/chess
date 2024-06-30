#include "chess.h"

int	disambiguate(char *san, char **move, char piece, t_move tmp, int takes)
{
	int	i;
	int	j;

	if (san[1] >= 'a' && san[1] <= 'h')
	{
		tmp.from[1] = san[1] - 'a';
		j = tmp.from[1];
		i = 0;
		while (i < 8)
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
			i++;
		}
	}
	else if (san[1] >= '1' && san[1] <= '8')
	{
		tmp.from[0] = san[1] - '1';
		i = tmp.from[0];
		j = 0;
		while (j < 8)
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
					disambiguate(san, &move, piece, tmp, takes);
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