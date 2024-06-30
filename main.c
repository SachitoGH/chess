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
char		player = 'w';

int	update_board(t_move move)
{
	t_square	empty = {{0, 0}, board[move.from[0]][move.from[1]].square_color};

	board[move.to[0]][move.to[1]].piece = board[move.from[0]][move.from[1]].piece;
	board[move.from[0]][move.from[1]] = empty;
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

int	verif_input(char *move)
{
	int	len;

	len = strlen(move);
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
	return (1);
}

int	main(void)
{
	char	team[2][6] = {
		{"white"},
		{"black"},
	};
	char	move[8];

	while (1)
	{
		print_board();
		player = *team[move_count % 2];
		printf("%s move: ", team[move_count % 2]);
		scanf("%s", move);
		if (verif_input(move))
			printf("%sSYNTAX ERROR%s\n", color("red"), color(0));
		else if (do_move(move))
			printf("%sILLEGAL MOVE%s\n", color("red"), color(0));
		else
			move_count++;
	}
	return (0);
}