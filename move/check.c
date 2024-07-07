#include "chess.h"

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

int king_under_attack(void)
{
	int		king_pos[2];

	locate_king(data.player, king_pos);
	if (my_piece_is_attacked(king_pos[0], king_pos[1]))
		return (1);
	return (0);
}

int	verif_kings(void)
{
	int	i;
	int	j;
	int	king;
	int pieces;

	king = 0;
	pieces = 0;
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (board[i][j].piece.name)
			{
				if (board[i][j].piece.name == 'k')
					king++;
				pieces++;
			}
			if (king == 2 && pieces > 2)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	verif_check(void)
{
	t_data	tmp;
	t_move  moves[218];
  	int 	legal;
	char	team[2][6] = {
		{"BLACK"},
		{"WHITE"},
	};

	save_data(&tmp, 0);
	if (verif_kings())
	{
		printf("%sDRAW%s\n", color("green"), color(0));
		printf("[%i]\n", data.move_chess);
		print_board();
		exit(0);
	}
  	legal = generate_legal_move(moves);
	if (king_under_attack())
  	{
    	if (!legal)
    	{               
    		printf("%sCHECKMATE %s WIN%s\n", color("green"), team[data.player == 'b'], color(0));
   			printf("[%i]\n", data.move_chess);
			print_board();
    		exit(0);                                  
    	}
    	else
    		printf("%sCHECK%s\n", color("green"), color(0));
	}
  	if (!legal)
	{
    	printf("%sSTALEMATE%s\n", color("green"), color(0));
    	printf("[%i]\n", data.move_chess);
		print_board();
    	exit(0);
	}
	save_data(&tmp, 1);
	return (0);
}