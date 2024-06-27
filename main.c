#include "chess.h"

int		move_count;
char	board[8][8] = {
	{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
	{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
	{'.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.'},
	{'.', '.', '.', '.', '.', '.', '.', '.'},
	{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
	{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
};

int	same_team(char p1, char p2)
{
	if ((p1 >= 'a' && p1 <= 'z' && p2 >= 'a' && p2 <= 'z') || (p1 >= 'A' && p1 <= 'Z' && p2 >= 'A' && p2 <= 'Z'))
		return (1);
	return (0);
}

int	pawn(char piece, int from[2], int to[2])
{
	int	dist_x;
	int	dist_y;

	dist_x = to[1] - from[1];
	dist_y = to[0] - from[0];
	// 2 squares move
	if (dist_y == 2 || dist_y == -2)
	{
		// check pawn can move 2 squares
		if (dist_x == 0 && ((piece == 'p' && from[0] == 6) || (piece == 'P' && from[0] == 1)))
			return (0);
	}
	// 1 square move
	else if (dist_y == 1 || dist_y == -1)
	{
		// capture a piece
		if (dist_x == 1 || dist_x == -1)
		{
			// check the piece exist and isnt in the the team of the pawn
			if (board[to[0]][to[1]] != '.' && !same_team(piece, board[to[0]][to[1]]))
				return (0);
		}
		// check the pawn dont go to a square with a piece
		else if (board[to[0]][to[1]] == '.')
			return (0);
	}
	return (1);
}

int	is_legal_move(int from[2], int to[2])
{
	char	piece;
	int		res;
	piece = board[from[0]][from[1]];

	if (piece == '.' || (move_count % 2 == 0 && (piece < 'a' || piece > 'z')) || (move_count % 2 == 1 && (piece < 'A' || piece > 'Z')))
		return (1);
	res = 0;
	if (piece == 'p' || piece == 'P')
		res = pawn(piece, from, to);
	// if (piece == 'r' || piece == 'R')
	// 	res = rock(board, from, to);
	// if (piece == 'n' || piece == 'N')
	// 	res = knight(board, from, to);
	// if (piece == 'b' || piece == 'B')
	// 	res = bishop(board, from, to);
	// if (piece == 'q' || piece == 'Q')
	// 	res = queen(board, from, to);
	// if (piece == 'k' || piece == 'K')
	// 	res = king(board, from, to);
	if (res)
		return (1);
	return (0);
}

int	convert_coord(char *str1, char *str2, int from[2], int to[2])
{
	from[0] = str1[1] - '1';
	from[1] = str1[0] - 'a';
	to[0] = str2[1] - '1';
	to[1] = str2[0] - 'a';
	from[0] += 7 - (from[0] * 2);
	to[0] += 7 - (to[0] * 2);
	return (0);
}

int	do_move(char *str1, char *str2)
{
	int	from[2];
	int	to[2];

	convert_coord(str1, str2, from, to);
	if (is_legal_move(from, to))
	{
		printf("ILLEGAL MOVE!\n");
		return(1);
	}
	board[to[0]][to[1]] = board[from[0]][from[1]];
	board[from[0]][from[1]] = '.';
	return (0);	
}

int	print_board(void)
{
	char	*color = "\033[0;31m"; //red
	char	*default_color = "\033[0m";
	int	i;
	int	j;

	i = 0;
	printf("%s  a b c d e f g h%s\n", color, default_color);
	while (i < 8)
	{
		printf("%s%c%s", color, '8' - i, default_color);
		j = 0;
		while (j < 8)
		{
			printf(" %c", board[i][j]);
			j++;
		}
		printf("%s %c%s\n", color, '8' - i, default_color);
		i++;
	}
	printf("%s  a b c d e f g h%s\n", color, default_color);
	return (0);
}

int	verif_input(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i])
		i++;
	if (i != 2 || (str1[0] < 'a' || str1[0] > 'h') || (str1[1] < '1' || str1[1] > '8'))
		return (1);
	i = 0;
	while (str2[i])
		i++;
	if (i != 2 || (str2[0] < 'a' || str2[0] > 'h') || (str2[1] < '1' || str2[1] > '8'))
		return (1);
	return (0);
}

int	main(void)
{
	char	color[2][6] = {
		{"white"},
		{"black"},
	};
	char	from[3];
	char	to[3];

	move_count = 0;
	while (1)
	{
		print_board();
		printf("%s move: ", color[move_count % 2]);
		scanf("%s %s", from, to);
		if (!verif_input(from, to) && !do_move(from, to))
			move_count++;
	}
	return (0);
}