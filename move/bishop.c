#include "chess.h"

int	move_diag(t_piece p, int from[2], int dist_x, int dist_y)
{
	int	x;
	int	y;

	if (dist_x == 0 || abs(dist_x) != abs(dist_y))
		return (1);
	x = 0;
	y = 0;
	while (x != dist_x || y != dist_y)
	{
		if (x != 0 && y != 0 && board[from[0] + y][from[1] + x].piece.name)
			return (1);
		if (dist_x > 0)
			x++;
		else
			x--;
		if (dist_y > 0)
			y++;
		else
			y--;
	}
	if (!board[from[0] + dist_y][from[1] + dist_x].piece.name || board[from[0] + dist_y][from[1] + dist_x].piece.team != p.team)
		return (0);
	return (1);
}

int	bishop(t_piece p, int from[2], int to[2])
{
	int	dist_x;
	int	dist_y;

	dist_x = to[1] - from[1];
	dist_y = to[0] - from[0];
	if (!move_diag(p, from, dist_x, dist_y))
		return (0);
	return (1);
}