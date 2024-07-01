#include "chess.h"

int	special_command(char *input)
{
	char	team[2][6] = {
		{"white"},
		{"black"},
	};
	char	input_2[10];
	t_move	move;

	if (!strcmp(input, "/help"))
	{
		printf("%s", color("cyan"));
		printf("command list:\n");
		printf("/undo : undo last move (max 1 move)\n");
		printf("/board : print the board\n");
		printf("/exit : exit the game\n");
		printf("/move : move arbitrary a piece on the board\n");
		printf("/draw : draw the game\n");
		printf("%s", color(0));
	}
	else if (!strcmp(input, "/undo"))
	{
		if (last_move.from[0] != 9) 
		{
			undo_move(last_move);
			last_move.from[0] = 9;
			move_count--;
			printf("%sUndo %s's last move%s\n", color("cyan"), team[move_count % 2], color(0));
		}
		else
			printf("%scan't undo%s\n", color("red"), color(0));
	}
	else if (!strcmp(input, "/board"))
		print_board();
	else if (!strcmp(input, "/move"))
	{
		printf("%senter move in coord: %s", color("cyan"), color(0));
		scanf("%4s", input_2);
		if (input_2[0] < 'a' || input_2[0] > 'h' || input_2[1] < '1' || input_2[1] > '8' || input_2[2] < 'a' || input_2[2] > 'h' || input_2[3] < '1' || input_2[3] > '8')
			printf("%sBAD SYNTAX%s\n", color("red"), color(0));
		else 
		{
			convert_coord(input_2, &move);
			update_board(move);
			piece_taken.name = 0;
			piece_taken.team = 0;
		}
	}
	else if (!strcmp(input, "/draw"))
	{
		printf("%sDRAW%s\n", color("green"), color(0));
		exit(0);
	}
	else if (!strcmp(input, "/exit"))
		exit(0);
	else
		printf("%scommand not found%s\n", color("red"), color(0));
	return (0);
}