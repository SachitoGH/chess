#include "chess.h"

int	promotion(t_move *move)
{
	if (!promote_to || promote_to == 'Q')
		board[move->to[0]][move->to[1]].piece.name = 'q';
	else if (promote_to == 'R')
		board[move->to[0]][move->to[1]].piece.name = 'r';
	else if (promote_to == 'N')
		board[move->to[0]][move->to[1]].piece.name = 'n';
	else if (promote_to == 'B')
		board[move->to[0]][move->to[1]].piece.name = 'b';
	promote_to = 0;
	return (0);
}