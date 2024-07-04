#include "chess.h"

int	undo_promotion(t_move move)
{
	board[move.to[0]][move.to[1]].piece.name = 'p';
	if (player == 'w')
		move.from[0] = move.to[0] + 1;
	else
		move.from[0] = move.to[0] - 1;
	undo_move(move);
	return (0);
}

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
	move->from[0] = 9;
	promote_to = 0;
	return (0);
}