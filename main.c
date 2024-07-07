#include "chess.h"

t_data	data = {0};
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

int get_player_move(t_move *move)
{
	char	input[10];
	char	team[2][6] = {
		{"white"},
		{"black"},
	};

	print_board();
	printf("(%i) %s move: ", data.move_chess, team[data.player == 'b']);
	scanf("%s9", input);
	if (input[0] == '/')
	{
		special_command(input);
		return (1);
	}
	else if (!verif_input(input))
	{
		printf("%sBAD SYNTAX%s\n", color("red"), color(0));
		return (1);
	}
	else if (!str_to_move(input, move))
	{
		printf("%sMOVE ILLEGAL%s\n", color("red"), color(0));
		return (1);
	}
	return (0);
}

int init_data()
{
	int	i;

	i = 0;
	data.move_count = 0;
	data.move_chess = 1;
	data.can_castle[0][0] = 1;
	data.can_castle[0][1] = 1;
	data.can_castle[1][0] = 1;
	data.can_castle[1][1] = 1;
	data.is_castle = 0;
	while (i < 8)
	{
		data.en_passant[0][i] = 0;
		data.en_passant[1][i] = 0;
		i++;
	}
	data.promote_to = 0;
	data.player = 'w';
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
	
	init_data();
	while (1)
	{
		ret = 0;
		if (data.player != *team[data.move_count % 2])
    	{
			// print_board();
			data.player = *team[data.move_count % 2];
			verif_check();
			reset_en_passant();
			data.is_castle = 0;
		}
		if (data.player == 'w')
			ret = get_ai_move(&move);
		else if (data.player == 'b')
			ret = get_player_move(&move);	
		if (!ret && !do_move(move))
		{
			printf("%sMOVE ILLEGAL%s\n", color("red"), color(0));
			print_board();
			// return (0);
		}
		else if (!ret)
		{
			if (data.player == 'b')
				data.move_chess++;
			data.move_count++;
			if (data.move_chess > 1000)
			{
				printf("+1000 coups\n");
				return(0);
			}
		}
	}
	return (0);
}
