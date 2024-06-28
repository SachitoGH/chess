#include "chess.h"

int	is_legal_move(int from[2], int to[2])
{
	t_piece	p;
	int		res;
	
	p = board[from[0]][from[1]].piece;
	if (!p.name || (move_count % 2 == 0 && p.team == 'b') || (move_count % 2 == 1 && p.team == 'w'))
		return (1);
	res = 0;
	if (p.name == 'p')
		res = pawn(p, from, to);
	if (p.name == 'r')
		res = rook(p, from, to);
	if (p.name == 'n')
		res = knight(p, from, to);
	if (p.name == 'b')
		res = bishop(p, from, to);
	if (p.name == 'q')
		res = queen(p, from, to);
	if (p.name == 'k')
		res = king(p, from, to);
	if (res)
		return (1);
	return (0);
}

int	do_move(char *str1, char *str2)
{
	int	from[2];
	int	to[2];

	convert_coord(str1, str2, from, to);
	if (is_legal_move(from, to))
	{
		printf("%sILLEGAL MOVE!%s\n", color("red"), color(0));
		return(1);
	}
	update_board(from, to);
	return (0);	
}