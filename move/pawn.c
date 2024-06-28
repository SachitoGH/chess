#include "chess.h"

int	pawn(t_piece p, int from[2], int to[2])
{
	int	dist_x;
	int	dist_y;

	dist_x = to[1] - from[1];
	dist_y = to[0] - from[0];
	// 2 squares move
	if (dist_y == 2 || dist_y == -2)
	{
		// check pawn can move 2 squares
		if (dist_x == 0 && ((p.team == 'w' && from[0] == 6) || (p.team == 'b' && from[0] == 1)))
		{
            // check path is free
            if (!board[to[0] - (dist_y / 2)][to[1]].piece.name && !board[to[0]][to[1]].piece.name)
                return (0);
        }
	}
	// 1 square move
	else if (dist_y == 1 || dist_y == -1)
	{
		// capture a piece
		if (dist_x == 1 || dist_x == -1)
		{
			// check the piece exist and isnt in the the team of the pawn
			if (board[to[0]][to[1]].piece.name && (board[to[0]][to[1]].piece.team != p.team))
				return (0);
		}
		// check the pawn dont go to a square with a piece
		else if (!board[to[0]][to[1]].piece.name)
			return (0);
	}
	return (1);
}