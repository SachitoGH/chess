#include "chess.h"

int	uncastling(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (data.can_castle[data.player == 'b'][0] == 0 && data.can_castle[data.player == 'b'][1] == 0)
		return (0);
	if (p.name == 'r')
	{
		if (data.can_castle[data.player == 'b'][0] == 1 && move.from[0] == row[data.player == 'b'] && move.from[1] == 0)
			data.can_castle[data.player == 'b'][0] = 0;
		if (data.can_castle[data.player == 'b'][1] == 1 && move.from[0] == row[data.player == 'b'] && move.from[1] == 7)
			data.can_castle[data.player == 'b'][1] = 0;
	}
	else if (p.name == 'k')
	{
		if (data.can_castle[data.player == 'b'][0] == 1)
			data.can_castle[data.player == 'b'][0] = 0;
		if (data.can_castle[data.player == 'b'][1] == 1)
			data.can_castle[data.player == 'b'][1] = 0;
	}
	return (0);
}

int	do_castle()
{
	t_move tmp;
	int	row[2] = {7, 0};

	tmp.from[0] = row[data.player == 'b'];
	tmp.from[1] = 4;
	tmp.to[0] = row[data.player == 'b'];
	if (data.is_castle == 1)
	{
		tmp.to[1] = 6;
		update_board(tmp);
		tmp.from[1] = 7;
		tmp.to[1] = 5;
		update_board(tmp);
		data.can_castle[data.player == 'b'][1] = 0;
	}
	if (data.is_castle == 2)
	{
		tmp.to[1] = 2;
		update_board(tmp);
		tmp.from[1] = 0;
		tmp.to[1] = 3;
		update_board(tmp);
		data.can_castle[data.player == 'b'][0] = 0;
	}
	return (0);
}

int	castling_verif(t_piece p, t_move move)
{
	int	row[2] = {7, 0};

	if (king_under_attack())
		return (1);
	if (data.can_castle[data.player == 'b'][1]  == 1)
	{
		if (board[row[data.player == 'b']][4].piece.name == 'k' && board[row[data.player == 'b']][7].piece.name == 'r' && !board[row[data.player == 'b']][5].piece.name && !board[row[data.player == 'b']][6].piece.name && !my_piece_is_attacked(row[data.player == 'b'], 5))
		{
			data.is_castle = 1;
			uncastling(p, move);
			return (0);
		}
	}
	if (data.can_castle[data.player == 'b'][0]  == 1)
	{
		if (board[row[data.player == 'b']][4].piece.name == 'k' && board[row[data.player == 'b']][0].piece.name == 'r' && !board[row[data.player == 'b']][1].piece.name && !board[row[data.player == 'b']][2].piece.name && !board[row[data.player == 'b']][3].piece.name && !my_piece_is_attacked(row[data.player == 'b'], 3))
		{
			data.is_castle = 2;
			uncastling(p, move);
			return (0);
		}
	}
	return (1);
}