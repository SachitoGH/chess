#include "chess.h"

char    *color(char *name)
{
    if (!name)
        return ("\033[0m"); //default color
    if (!strcmp(name, "purple"))
        return ("\033[1;35m");
    if (!strcmp(name, "white"))
        return ("\033[1;37m");
    if (!strcmp(name, "red"))
        return ("\033[1;31m");
    if (!strcmp(name, "yellow"))
        return ("\033[1;33m");
    if (!strcmp(name, "green"))
        return ("\033[1;32m");
    if (!strcmp(name, "cyan"))
        return ("\033[1;36m");
    if (!strcmp(name, "black"))
        return ("\e[1;30m");
    return ("\033[0m");
}
int inside_board(char letter, char number)
{
    if ((letter >= 'a' && letter <= 'h') && (number >= '1' && number <= '8'))
        return (1);
    return (0);
}       

int is_piece(char p)
{
    if (p == 'P' || p == 'R' || p == 'N' || p == 'B' || p == 'Q' || p == 'K')
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

void	print_board(void)
{
	int		i;
	int		j;

	i = 0;
	// printf("%s  a b c d e f g h%s\n", color("red"), color(0));
	while (i < 8)
	{
		printf("%s%c%s", color(COORD_COLOR), '8' - i, color(0));
		j = 0;
		while (j < 8)
		{
			if (!board[i][j].piece.name)
			{
				if (board[i][j].square_color == 'w')
					printf("%s .%s", color(WHITE_COLOR), color(0));
				else
					printf("%s .%s", color(BLACK_COLOR), color(0));
			}
			else if (board[i][j].piece.team == player && board[i][j].piece.name == 'k' && my_piece_is_attacked(i, j))
				printf("%s %c%s", color("red"), board[i][j].piece.name - 32, color(0));
			else if (board[i][j].piece.team == 'w' && board[i][j].piece.name == 'p')
				printf("%s %c%s", color(WHITE_COLOR), board[i][j].piece.name, color(0));
			else if (board[i][j].piece.team == 'w')
				printf("%s %c%s", color(WHITE_COLOR), board[i][j].piece.name - 32, color(0));
			else if (board[i][j].piece.name == 'p')
				printf("%s %c%s", color(BLACK_COLOR), board[i][j].piece.name, color(0));
			else
				printf("%s %c%s", color(BLACK_COLOR), board[i][j].piece.name - 32, color(0));
			j++;
		}
		// printf("%s %c%s", color("red"), '8' - i, color(0));
		printf("\n");
		i++;
	}
	printf("%s  a b c d e f g h%s\n", color(COORD_COLOR), color(0));
}

int	verif_input(char *move)
{
	int	len;

	len = strlen(move);
	if (move[len - 2] == '=' && is_piece(move[len - 1]))
	{
		promote_to = move[len - 1];
		len -= 2;
	}
	if (len > 5)
		return (1);
	if (len == 2 && inside_board(move[0], move[1]))
		return (0);
	if (len == 3 && is_piece(move[0]) && inside_board(move[1], move[2]))
		return (0);
	if (len == 4 && ((is_piece(move[0]) && inside_board(move[2], move[3])) ||
		((move[0] >= 'a' && move[0] <= 'h') && move[1] == 'x' && inside_board(move[2], move[3]))))
		return (0);
	if (len == 5 && is_piece(move[0]) && ((move[1] >= 'a' && move[1] <= 'h') || (move[1] >= '1' && move[1] <= '8')) &&
		move[2] == 'x' && inside_board(move[3], move[4]))
		return (0);
	if (!strcmp(move, "O-O") || !strcmp(move, "O-O-O"))
		return (0);
	return (1);
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
  	int 	legal;
	char	team[2][6] = {
		{"BLACK"},
		{"WHITE"},
	};

	save_data(0);
	if (verif_kings())
	{
		printf("%sDRAW%s\n", color("green"), color(0));
		printf("[%i]\n", move_chess);
		print_board();
		exit(0);
	}
  	legal = search_legal_move();
	if (king_under_attack())
  	{
    	if (!legal)
    	{               
    		printf("%sCHECKMATE %s WIN%s\n", color("green"), team[move_count % 2], color(0));
   			printf("[%i]\n", move_chess);
			print_board();
    		exit(0);                                  
    	}
    	else
    		printf("%sCHECK%s\n", color("green"), color(0));
	}
  	if (!legal)
	{
    	printf("%sSTALEMATE%s\n", color("green"), color(0));
    	printf("[%i]\n", move_chess);
		print_board();
    	exit(0);
	}
	save_data(1);
	return (0);
}

int	reset_en_passant(void)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		en_passant[(move_count) % 2][i] = 0;
		i++;
	}
	return (0);
}

int save_data(int mode)
{
	static int 		ep[2][8];
	static int 		cc[2][2];
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (i < 8)
		{
			ep[(move_count % 2) + 1][i] = en_passant[(move_count % 2) + 1][i];
			i++;
		}
		i = 0;
		while (i < 2)
		{
			cc[move_count % 2][i] = can_castle[move_count % 2][i];
			i++;
		}
	}
	else if (mode == 1)
	{
		while (i < 8)
		{
			en_passant[(move_count % 2) + 1][i] = ep[(move_count % 2) + 1][i];
			i++;
		}
		i = 0;
		while (i < 2)
		{
			can_castle[move_count % 2][i] = cc[move_count % 2][i];
			i++;
		}
	}
	return (0);
}