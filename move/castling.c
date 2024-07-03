#include "chess.h"

int	uncastling(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (can_castle[move_count % 2][0] == 0 && can_castle[move_count % 2][1] == 0)
		return (0);
	if (p.name == 'r')
	{
		if (can_castle[move_count % 2][0] == 1 && move.from[0] == row[move_count % 2] && move.from[1] == 0)
			can_castle[move_count % 2][0] = 0;
		if (can_castle[move_count % 2][1] == 1 && move.from[0] == row[move_count % 2] && move.from[1] == 7)
			can_castle[move_count % 2][1] = 0;
	}
	else if (p.name == 'k')
	{
		if (can_castle[move_count % 2][0] == 1)
			can_castle[move_count % 2][0] = 0;
		if (can_castle[move_count % 2][1] == 1)
			can_castle[move_count % 2][1] = 0;
	}
	return (0);
}

int	undo_castle(t_move move)
{
	t_move tmp;
	int	row[2] = {7, 0};

	tmp.from[0] = row[move_count % 2];
	tmp.to[0] = row[move_count % 2];
	if (move.to[1] == 0)
	{
		tmp.from[1] = 6;
		tmp.to[1] = 4;
		update_board(tmp);
		tmp.from[1] = 5;
		tmp.to[1] = 7;
		update_board(tmp);
		can_castle[move_count % 2][1] = 1;
	}
	if (move.to[1] == 1)
	{
		tmp.from[1] = 2;
		tmp.to[1] = 4;
		update_board(tmp);
		tmp.from[1] = 3;
		tmp.to[1] = 0;
		update_board(tmp);
		can_castle[move_count % 2][0] = 1;
	}
	return (0);
}
int	do_castle(t_move move)
{
	t_move tmp;
	int	row[2] = {7, 0};

	tmp.from[0] = row[move_count % 2];
	tmp.from[1] = 4;
	tmp.to[0] = row[move_count % 2];
	if (move.to[1] == 0)
	{
		tmp.to[1] = 6;
		update_board(tmp);
		tmp.from[1] = 7;
		tmp.to[1] = 5;
		update_board(tmp);
		can_castle[move_count % 2][1] = 0;
	}
	if (move.to[1] == 9)
	{
		tmp.to[1] = 2;
		update_board(tmp);
		tmp.from[1] = 0;
		tmp.to[1] = 3;
		update_board(tmp);
		can_castle[move_count % 2][0] = 0;
	}
	return (0);
}

int	castling_verif(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (king_under_attack())
		return (1);
	if (move.to[1] == 0 && can_castle[move_count % 2][1]  == 1)
	{
		if (board[row[move_count % 2]][4].piece.name == 'k' && board[row[move_count % 2]][7].piece.name == 'r' && !board[row[move_count % 2]][5].piece.name && !board[row[move_count % 2]][6].piece.name && !my_piece_is_attacked(row[move_count % 2], 5))
		{
			uncastling(p, move);
			return (0);
		}
	}
	if (move.to[1] == 9 && can_castle[move_count % 2][0]  == 1)
	{
		if (board[row[move_count % 2]][4].piece.name == 'k' && board[row[move_count % 2]][0].piece.name == 'r' && !board[row[move_count % 2]][1].piece.name && !board[row[move_count % 2]][2].piece.name && !board[row[move_count % 2]][3].piece.name && !my_piece_is_attacked(row[move_count % 2], 3))
		{
			uncastling(p, move);
			return (0);
		}
	}
	return (1);
}