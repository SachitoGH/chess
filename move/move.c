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

int	do_move(char *move_str)
{
	t_move	move;

	// if san input
	move_str = san_to_coord(move_str);
	if (!move_str)
		return (1);
	convert_coord(move_str, &move);
	free(move_str);
	printf("board[%i][%i] to board[%i][%i]\n", move.from[0], move.from[1], move.to[0], move.to[1]);
	if (is_legal_move(move))
		return(1);
	update_board(move);
	return (0);	
}