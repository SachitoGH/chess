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
char		player = 0;
char		promote_to;
int			move_chess = 1;

int get_player_move(t_move *move)
{
	char	input[10];
	char	team[2][6] = {
		{"white"},
		{"black"},
	};

	printf("(%i) %s move: ", move_chess, team[move_count % 2]);
	scanf("%s9", input);
	if (input[0] == '/')
	{
		special_command(input);
		return (1);
	}
	else if (verif_input(input))
	{
		printf("%sBAD SYNTAX%s\n", color("red"), color(0));
		return (1);
	}
	else if (str_to_move(input, move))
	{
		printf("%sMOVE ILLEGAL%s\n", color("red"), color(0));
		return (1);
	}
	return (0);
}

int	main(void)
{
	char	team[2][6] = {
		{"white"},
		{"black"},
	};
	t_move	move;
	int		ret;
	
	srand(time(NULL));
	while (1)
	{
		ret = 0;
		if (player != *team[move_count % 2])
    	{
			// printf("score: %i\n", evaluation());
			print_board();
			player = *team[move_count % 2];
			verif_check();
			reset_en_passant();
		}
		if (player == 'w')
			ret = get_player_move(&move);
		else if (player == 'b')
			ret = get_player_move(&move);	
		if (!ret && do_move(&move))
		{
			printf("%sMOVE ILLEGAL%s\n", color("red"), color(0));
			print_board();
		}
		else if (!ret)
		{
			if (player == 'b')
				move_chess++;
			move_count++;
			if (move_chess > 1000)
			{
				printf("+1000 coups\n");
				return(0);
			}
		}
	}
	return (0);
}
