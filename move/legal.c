#include "chess.h"

int	is_legal_move(t_move move)
{
	t_piece	p;
	int		res;
	
	p = board[move.from[0]][move.from[1]].piece;
	if (!p.name || p.team != player)
		return (1);
	res = 0;
	if (p.name == 'p')
		res = pawn(p, move);
	if (p.name == 'r')
		res = rook(p, move);
	if (p.name == 'n')
		res = knight(p, move);
	if (p.name == 'b')
		res = bishop(p, move);
	if (p.name == 'q')
		res = queen(p, move);
	if (p.name == 'k')
		res = king(p, move);
	if (res)
		return (1);
	return (0);
}

int	can_move(t_move *move)
{
	int		i;
	int		j;

	i = 0;
	while (i < 8)
	{
		move->to[0] = i; 
		j = 0;
		while (j < 8)
		{
			move->to[1] = j;
			if (!do_move(move))
			{
				undo_move(*move);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	search_legal_move(void)
{
	t_move move;
	int legal_move;
	int	i;
	int	j;

	legal_move = 0;
	i = 0;
	while (i < 8)
	{
		move.from[0] = i;
		j = 0;
		while (j < 8)
		{
			move.from[1] = j;
			if (board[i][j].piece.team == player)
				if (can_move(&move))
					legal_move++;
			j++;
		}
		i++;
	}
	return (legal_move);
}


int	get_move(t_move *move, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		move->from[0] = i;
		j = 0;
		while (j < 8)
		{
			move->from[1] = j;
			if (board[i][j].piece.team == player)
			{
				if (can_move(move))
				{
					if (count == 1)
						return (0);
					else
						count--;
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}