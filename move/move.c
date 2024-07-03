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

int	locate_king(char team, int king_pos[2])
{
	t_piece	piece;
	int		i;
	int		j;

	i = 0;
	while (i < 8) 
	{
		j = 0;
		while (j < 8)
		{
			piece = board[i][j].piece;
			if (piece.name == 'k' && piece.team == team)
			{
				king_pos[0] = i;
				king_pos[1] = j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
int	my_piece_is_attacked(int pos_x, int pos_y)
{
	int	i;
	int	j;
	t_move move;

	change_player();
	move.to[0] = pos_x;
	move.to[1] = pos_y;
	i = 0;
	while (i < 8)
	{
		move.from[0] = i;
		j = 0;
		while (j < 8)
		{
			move.from[1] = j;
			if (!is_legal_move(move))
			{
				change_player();
				return (1);
			}
			j++;
		}
		i++;
	}
	change_player();
	return (0);
}
void	change_player(void)
{
	if (player == 'w')
		player = 'b';
	else
		player = 'w';
}

int king_under_attack(void)
{
	int		king_pos[2];

	locate_king(player, king_pos);
	if (my_piece_is_attacked(king_pos[0], king_pos[1]))
		return (1);
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