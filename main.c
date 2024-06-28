#include "chess.h"

int			move_count = 0;
t_square	board[8][8] = {
	{{{'r', 'b'}, 'w'}, {{'n', 'b'}, 'b'}, {{'b', 'b'}, 'w'}, {{'q', 'b'}, 'b'}, {{'k', 'b'}, 'w'}, {{'b', 'b'}, 'b'}, {{'n', 'b'}, 'w'}, {{'r', 'b'}, 'b'}},
    {{{'p', 'b'}, 'b'}, {{'p', 'b'}, 'w'}, {{'p', 'b'}, 'b'}, {{'p', 'b'}, 'w'}, {{'p', 'b'}, 'b'}, {{'p', 'b'}, 'w'}, {{'p', 'b'}, 'b'}, {{'p', 'b'}, 'w'}},
    {{{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}},
    {{{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}},
    {{{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}},
    {{{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}, {{0, 0}, 'b'}, {{0, 0}, 'w'}},
    {{{'p', 'w'}, 'w'}, {{'p', 'w'}, 'b'}, {{'p', 'w'}, 'w'}, {{'p', 'w'}, 'b'}, {{'p', 'w'}, 'w'}, {{'p', 'w'}, 'b'}, {{'p', 'w'}, 'w'}, {{'p', 'w'}, 'b'}},
    {{{'r', 'w'}, 'b'}, {{'n', 'w'}, 'w'}, {{'b', 'w'}, 'b'}, {{'q', 'w'}, 'w'}, {{'k', 'w'}, 'b'}, {{'b', 'w'}, 'w'}, {{'n', 'w'}, 'b'}, {{'r', 'w'}, 'w'}}
};

int	update_board(int from[2], int to[2])
{
	t_square	empty = {{0, 0}, board[from[0]][from[1]].square_color};

	board[to[0]][to[1]].piece = board[from[0]][from[1]].piece;
	board[from[0]][from[1]] = empty;
	return (0);
}

int	print_board(void)
{
	int		i;
	int		j;

	i = 0;
	// printf("%s  a b c d e f g h%s\n", color("red"), color(0));
	while (i < 8)
	{
		printf("%s%c%s", color("red"), '8' - i, color(0));
		j = 0;
		while (j < 8)
		{
			if (!board[i][j].piece.name)
			{
				if (board[i][j].square_color == 'w')
					printf(" .");
				else
					printf("%s .%s", color("purple"), color(0));
			}
			else if (board[i][j].piece.team == 'w')
				printf(" %c", board[i][j].piece.name);
			else
				printf("%s %c%s", color("purple"), board[i][j].piece.name, color(0));
			j++;
		}
		// printf("%s %c%s", color("red"), '8' - i, color(0));
		printf("\n");
		i++;
	}
	printf("%s  a b c d e f g h%s\n", color("red"), color(0));
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