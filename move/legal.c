#include "chess.h"

int	is_legal_move(t_move move)
{
	t_piece	p;
	int		res;

	p = board[move.from[0]][move.from[1]].piece;
	if (!p.name || p.team != data.player)
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

int can_move(t_move move[218], int *count, int a, int b)
{
    int i, j;
    t_square clone[8][8];
    t_data tmp;

    clone_board(clone, 0);
    save_data(&tmp, 0);
	i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
	        move[*count].from[0] = a;
            move[*count].from[1] = b;
			move[*count].to[0] = i; 
            move[*count].to[1] = j;
            if (do_move(move[*count]))
            {
                clone_board(clone, 1);                
                (*count)++;
            }
            save_data(&tmp, 1);
            j++;
        }
        i++;
    }
    return (0);
}

int generate_legal_move(t_move move[218])
{
    int count;
    int i, j;

    count = 0;
    i = 0;

    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].piece.team == data.player)
                can_move(move, &count, i, j);
            j++;
        }
        i++;
    }
    return (count);
}
