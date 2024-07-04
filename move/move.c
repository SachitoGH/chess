#include "chess.h"

int	update_board(t_move move)
{
	t_square	empty = {{0, 0}, board[move.from[0]][move.from[1]].square_color};

	board[move.to[0]][move.to[1]].piece = board[move.from[0]][move.from[1]].piece;
	board[move.from[0]][move.from[1]] = empty;
	return (0);
}

void clone_board(t_square clone[8][8], int mode) 
{
	if (mode == 0)
    	memcpy(clone, board, 8 * 8 * sizeof(t_square));
	else
    	memcpy(board, clone, 8 * 8 * sizeof(t_square));

}

int	do_move(t_move *move)
{
    t_square clone[8][8];

	clone_board(clone, 0);
	if (is_legal_move(*move))
		return(1);
	if (move->to[0] == 9)
		do_castle(*move);
	else
		update_board(*move);
	if (king_under_attack())
	{
		if (en_passant[(move_count % 2) + 1][move->to[1]] == 2)
			en_passant[(move_count % 2) + 1][move->to[1]] = 1;
		clone_board(clone, 1);
		return (1);
	}
	if (board[move->to[0]][move->to[1]].piece.name == 'p' && ((move->to[0] == 7 && player == 'b') || (move->to[0] == 0 && player == 'w')))
		promotion(move);
	return (0);	
}