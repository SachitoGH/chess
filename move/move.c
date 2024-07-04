#include "chess.h"

int	update_board(t_move move)
{
	t_square	empty = {{0, 0}, board[move.from[0]][move.from[1]].square_color};

	board[move.to[0]][move.to[1]].piece = board[move.from[0]][move.from[1]].piece;
	board[move.from[0]][move.from[1]] = empty;
	return (0);
}

int	undo_move(t_move move)
{
	t_move undo;

	if (move.to[0] == 9)
		undo_castle(move);
	if (move.from[0] == 9)
		undo_promotion(move);
	if (en_passant[(move_count + 1) % 2][move.to[1]] == 2)
		undo_en_passant(move);
	else
	{
		undo.from[0] = move.to[0];
		undo.from[1] = move.to[1];
		undo.to[0] = move.from[0];
		undo.to[1] = move.from[1];
		update_board(undo);
		if (piece_taken.name)
			board[undo.from[0]][undo.from[1]].piece = piece_taken;
	}
	return (0);
}

int	do_move(t_move *move)
{
	if (is_legal_move(*move))
		return(1);
	if (move->to[0] == 9)
		do_castle(*move);
	else
	{
		piece_taken = board[move->to[0]][move->to[1]].piece;
		update_board(*move);
	}
	if (king_under_attack())
	{
		undo_move(*move);
		return (1);
	}
	if (board[move->to[0]][move->to[1]].piece.name == 'p' && ((move->to[0] == 7 && player == 'b') || (move->to[0] == 0 && player == 'w')))
		promotion(move);
	return (0);	
}