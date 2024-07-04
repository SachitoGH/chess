#include "chess.h"

int	get_ia_move(t_move *move)
{
	int	legal;
	int	rand_legal;

	save_data(0);
	// srand(time(NULL));
	legal = search_legal_move();
	rand_legal = (legal / 2) + 1;
    // rand_legal = (rand() % legal) + 1;
	get_move(move, rand_legal);
	save_data(1);
	return (0);
}