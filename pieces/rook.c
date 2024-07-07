#include "chess.h"

int	move_straight(t_piece p, int from[2], int dist_x, int dist_y)
{
	int	i;
	
	if (dist_x && dist_y)
		return (1);
	i = 0;
	if (dist_x)
	{
		while (i != dist_x)
		{
			if (i != 0 && board[from[0]][from[1] + i].piece.name)
				return (1);
			if (dist_x > 0)
				i++;
			else
				i--;
		}
		if (!board[from[0]][from[1] + dist_x].piece.name || board[from[0]][from[1] + dist_x].piece.team != p.team)
			return (0);
	}
	else if (dist_y)
	{
		while (i != dist_y)
		{
			if (i != 0 && board[from[0] + i][from[1]].piece.name)
				return (1);
			if (dist_y > 0)
				i++;
			else
				i--;
		}
		if (!board[from[0] + dist_y][from[1]].piece.name || board[from[0] + dist_y][from[1]].piece.team != p.team)
			return (0);
	}
	return (1);
}

int	rook(t_piece p, t_move move)
{
	int	dist_x;
	int	dist_y;

	dist_x = move.to[1] - move.from[1];
	dist_y = move.to[0] - move.from[0];
	if (!move_straight(p, move.from, dist_x, dist_y))
	{
		if (data.can_castle[data.player == 'b'][0] == 1 || data.can_castle[data.player == 'b'][0] == 1) 
			uncastling(p, move);
		return (0);	
	}
	return (1);
}