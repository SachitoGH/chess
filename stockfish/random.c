#include "chess.h"

int get_rand_number(int min, int max) 
{
    return (rand() % (max - min + 1) + min);
}

int	get_ia_move(t_move *move)
{
	int	legal;
	int	rand_legal;

	legal = search_legal_move();

	if (legal)
	{
		rand_legal = get_rand_number(1, legal);
		if(get_move(move, rand_legal))
			return (1);
	}
	else
		return(1);
	return (0);
}