#include "chess.h"

int	uncastling(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (can_castle[player == 'b'][0] == 0 && can_castle[player == 'b'][1] == 0)
		return (0);
	if (p.name == 'r')
	{
		if (can_castle[player == 'b'][0] == 1 && move.from[0] == row[player == 'b'] && move.from[1] == 0)
			can_castle[player == 'b'][0] = 0;
		if (can_castle[player == 'b'][1] == 1 && move.from[0] == row[player == 'b'] && move.from[1] == 7)
			can_castle[player == 'b'][1] = 0;
	}
	else if (p.name == 'k')
	{
		if (can_castle[player == 'b'][0] == 1)
			can_castle[player == 'b'][0] = 0;
		if (can_castle[player == 'b'][1] == 1)
			can_castle[player == 'b'][1] = 0;
	}
	return (0);
}

int	do_castle()
{
	t_move tmp;
	int	row[2] = {7, 0};

	tmp.from[0] = row[player == 'b'];
	tmp.from[1] = 4;
	tmp.to[0] = row[player == 'b'];
	if (is_castle == 1)
	{
		tmp.to[1] = 6;
		update_board(tmp);
		tmp.from[1] = 7;
		tmp.to[1] = 5;
		update_board(tmp);
		can_castle[player == 'b'][1] = 0;
	}
	if (is_castle == 2)
	{
		tmp.to[1] = 2;
		update_board(tmp);
		tmp.from[1] = 0;
		tmp.to[1] = 3;
		update_board(tmp);
		can_castle[player == 'b'][0] = 0;
	}
	return (0);
}

int	castling_verif(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (king_under_attack())
		return (1);
	if (can_castle[player == 'b'][1]  == 1)
	{
		if (board[row[player == 'b']][4].piece.name == 'k' && board[row[player == 'b']][7].piece.name == 'r' && !board[row[player == 'b']][5].piece.name && !board[row[player == 'b']][6].piece.name && !my_piece_is_attacked(row[player == 'b'], 5))
		{
			printf("castle king side\n");
			is_castle = 1;
			uncastling(p, move);
			return (0);
		}
	}
	if (can_castle[player == 'b'][0]  == 1)
	{
		if (board[row[player == 'b']][4].piece.name == 'k' && board[row[player == 'b']][0].piece.name == 'r' && !board[row[player == 'b']][1].piece.name && !board[row[player == 'b']][2].piece.name && !board[row[player == 'b']][3].piece.name && !my_piece_is_attacked(row[player == 'b'], 3))
		{
			printf("castle queen side\n");
			is_castle = 2;
			uncastling(p, move);
			return (0);
		}
	}
	return (1);
}