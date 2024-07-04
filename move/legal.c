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

int	is_the_move(t_move *move, int *count, t_square clone[8][8])
{
	int		i;
	int		j;

	i = 0;
	save_data(0);
	while (i < 8)
	{
		move->to[0] = i; 
		j = 0;
		while (j < 8)
		{
			move->to[1] = j;
			if (!do_move(move))
			{
				clone_board(clone, 1);
				save_data(1);
				(*count)--;
			}
			if (*count == 0)
				return (1);
			j++;
		}
		i++;
	}
	save_data(1);
	return (0);
}

int	can_move(t_move *move, t_square clone[8][8])
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	save_data(0);

	while (i < 8)
	{
		move->to[0] = i; 
		j = 0;
		while (j < 8)
		{
			move->to[1] = j;
			if (!do_move(move))
			{
				clone_board(clone, 1);				
				count++;
			}
			save_data(1);
			j++;
		}
		i++;
	}
	return (count);
}

int	search_legal_move(void)
{
	t_move move;
	t_square clone[8][8];
	int legal_move;
	int	i;
	int	j;

	legal_move = 0;
	i = 0;
	clone_board(clone, 0);
	while (i < 8)
	{
		move.from[0] = i;
		j = 0;
		while (j < 8)
		{
			move.from[1] = j;
			if (board[i][j].piece.team == player)
				legal_move += can_move(&move, clone);
			j++;
		}
		i++;
	}
	return (legal_move);
}


int	get_move(t_move *move, int count)
{
	t_square clone[8][8];
	int	i;
	int	j;

	i = 0;
	clone_board(clone, 0);
	while (i < 8)
	{
		move->from[0] = i;
		j = 0;
		while (j < 8)
		{
			move->from[1] = j;
			if (board[i][j].piece.team == player)
			{
				if (is_the_move(move, &count, clone))
					return(0);
			}
			j++;
		}
		i++;
	}
	return (1);
}