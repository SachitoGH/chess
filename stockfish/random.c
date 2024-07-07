#include "chess.h"

int get_rand_number(int min, int max) 
{
    return (rand() % (max - min + 1) + min);
}

int	get_ai_move_random(t_move *move)
{
	int	legal;
	int	rand_legal;
	t_move moves[218];

	srand(time(NULL));
	legal = generate_legal_move(moves);
	if (legal)
	{
		rand_legal = get_rand_number(0, legal - 1);
		*move = moves[rand_legal];
	}
	else
		return(1);
	return (0);
}

