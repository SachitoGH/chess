#include "chess.h"

int			en_passant[2][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
int			can_castle[2][2] = {{1, 1}, {1, 1}};
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
t_piece		piece_taken;
t_move		last_move = {{9, 9}, {9, 9}};
char		promote_to;
int			move_chess = 1;

int	update_board(t_move move)
{
	t_square	empty = {{0, 0}, board[move.from[0]][move.from[1]].square_color};

	board[move.to[0]][move.to[1]].piece = board[move.from[0]][move.from[1]].piece;
	board[move.from[0]][move.from[1]] = empty;
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

int	can_move(int x, int y)
{
	int		i;
	int		j;
	t_move	move;

	move.from[0] = x;
	move.from[1] = y;
	i = 0;
	while (i < 8)
	{
		move.to[0] = i; 
		j = 0;
		while (j < 8)
		{
			move.to[1] = j;
			if (!do_move(&move))
			{
				undo_move(move);
				// printf("move : %i %i to %i %i possible\n", move.from[0], move.from[1], move.to[0], move.to[1]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	checkmate(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (board[i][j].piece.team == player)
				if (can_move(i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	verif_check(void)
{
	t_piece tmp_p;
	int		tmp_ep[2][8];
	int	i;

	i = 0;
	while (i < 8)
	{
		tmp_ep[(move_count) % 2][i] = en_passant[(move_count) % 2][i];
		i++;
	}
	tmp_p = piece_taken;
	if (!checkmate())
	{
		printf("%sCHECKMATE%s\n", color("green"), color(0));
		print_board();
		return (1);
	}
	if (king_under_attack())
		printf("(%sCHECK%s)", color("green"), color(0));
	piece_taken = tmp_p;
	i = 0;
	while (i < 8)
	{
		en_passant[(move_count) % 2][i] = tmp_ep[(move_count) % 2][i];
		i++;
	}
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

void print_en_passant(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 8)
		{
			printf("%i ", en_passant[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(void)
{
	char	team[2][6] = {
		{"white"},
		{"black"},
	};
	char	input[10];
	t_move	move;
	
	while (1)
	{
		player = *team[move_count % 2];
		if (verif_check())
			return (0);
		printf("(%i) %s move: ", move_chess, team[move_count % 2]);
		scanf("%s9", input);
		if (input[0] == '/')
			special_command(input);
		else
		{
			reset_en_passant();
			if (verif_input(input))
				printf("%sBAD SYNTAX%s\n", color("red"), color(0));
			else if (str_to_move(input, &move) || do_move(&move))
				printf("%sMOVE ILLEGAL%s\n", color("red"), color(0));
			else
			{
				last_move = move;
				if (player == 'b')
					move_chess++;
				move_count++;
			}
		}
	}
	return (0);
}
