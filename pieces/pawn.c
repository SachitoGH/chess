#include "chess.h"

int	pawn(t_piece p, t_move move)
{
	int	dist_x;
	int	dist_y;
	int	en_passant_row[2] = {2, 5};

	dist_x = move.to[1] - move.from[1];
	dist_y = move.to[0] - move.from[0];
	if ((dist_y == 1 && p.team == 'w') || (dist_y == -1 && p.team  == 'b') || (dist_x > 1 || dist_x < -1))
		return (1);
	// 2 squares move
	if (dist_y == 2 || dist_y == -2)
	{
		// check pawn can move 2 squares
		if (dist_x == 0 && ((p.team == 'w' && move.from[0] == 6) || (p.team == 'b' && move.from[0] == 1)))
		{
            // check path is free
            if (!board[move.to[0] - (dist_y / 2)][move.to[1]].piece.name && !board[move.to[0]][move.to[1]].piece.name)
            {
				en_passant[move_count % 2][move.from[1]] = 1;
				return (0);
			}
		}
	}
	// 1 square move
	else if (dist_y == 1 || dist_y == -1)
	{
		// capture a piece
		if (dist_x == 1 || dist_x == -1)
		{
			// en passant
			if (move.to[0] == en_passant_row[move_count % 2] && en_passant[(move_count + 1) % 2][move.to[1]] == 1)
			{
				en_passant_row[0]++;
				en_passant_row[1]--;
				board[move.to[0]][move.to[1]].piece = board[en_passant_row[move_count % 2]][move.to[1]].piece;
				board[en_passant_row[move_count % 2]][move.to[1]].piece.name = 0;
				board[en_passant_row[move_count % 2]][move.to[1]].piece.team = 0;
				return (0);
			}
			// check the piece exist and isnt in the the team of the pawn
			if (board[move.to[0]][move.to[1]].piece.name && (board[move.to[0]][move.to[1]].piece.team != p.team))
				return (0);
		}
		// check the pawn dont go to a square with a piece
		else if (!board[move.to[0]][move.to[1]].piece.name)
			return (0);
	}
	return (1);
}