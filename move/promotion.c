#include "chess.h"

int	promotion(t_move move)
{
	if (!data.promote_to || data.promote_to == 'Q')
		board[move.to[0]][move.to[1]].piece.name = 'q';
	else if (data.promote_to == 'R')
		board[move.to[0]][move.to[1]].piece.name = 'r';
	else if (data.promote_to == 'N')
		board[move.to[0]][move.to[1]].piece.name = 'n';
	else if (data.promote_to == 'B')
		board[move.to[0]][move.to[1]].piece.name = 'b';
	data.promote_to = 0;
	return (0);
}