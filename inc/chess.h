#ifndef CHESS_H
# define CHESS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <time.h>
# include <limits.h>

# define WHITE_COLOR "white"
# define BLACK_COLOR "purple"
# define COORD_COLOR "yellow"

typedef struct s_piece
{
	char	name;
	char	team;
}	t_piece;

typedef struct s_square
{
    t_piece	piece;
	char	square_color;
}   t_square;

typedef struct s_move
{
	int	from[2];
	int	to[2];
}	t_move;

typedef struct s_data
{
	int		move_count;
	int		move_chess;
	int		can_castle[2][2]; // [0] = white [1] = black [.][0] = left [.][1] = right
	int		is_castle;
	int		en_passant[2][8];
	char	promote_to;
	char	player;
}	t_data;

// global var;
extern t_data	data;
extern t_square	board[8][8];

// stockfish
// minimax.c
int	get_ai_move(t_move *move);

// random.c
int	get_ai_move_random(t_move *move);

// evaluation.c
int evaluation_current(void);
int evaluation(void);

// utils
// command.c
int		special_command(char *input);

// conversion.c
char	*san_to_coord(char *move_str);
int		str_to_move(char *move_str, t_move *move);
int		convert_coord(char *move_str, t_move *move);

// utils
int		update_board(t_move move);
void	print_board(void);
int		verif_input(char *move);
char    *color(char *name);
char    *color_bg(char *name);
int 	inside_board(char letter, char number);
int 	is_piece(char p);
int		change_player(void);
int		reset_en_passant(void);
int 	save_data(t_data *tmp, int mode);

// move
// move.c
int	update_board(t_move move);
int	do_move(t_move move);
void clone_board(t_square clone[8][8], int mode);

// check.c
int		locate_king(char team, int king_pos[2]);
int		my_piece_is_attacked(int pos_x, int pos_y);
int 	king_under_attack(void);
int		verif_check(void);

// promotion.c
int	promotion(t_move move);

// castling.c
int	do_castle();
int	castling_verif(t_piece p, t_move move);
int	uncastling(t_piece p, t_move move);

// legal.c
int	is_legal_move(t_move move);
int can_move(t_move move[218], int *count, int a, int b);
int	generate_legal_move(t_move move[218]);


// pieces
// pawn.c
int	pawn(t_piece p, t_move move);

// bishop.c
int	move_diag(t_piece p, int from[2], int dist_x, int dist_y);
int	bishop(t_piece p, t_move move);

// knight.c
int knight(t_piece p, t_move move);

// rook.c
int	move_straight(t_piece p, int from[2], int dist_x, int dist_y);
int	rook(t_piece p, t_move move);

// queen.c
int queen(t_piece p, t_move move);

// king.c
int king(t_piece p, t_move move);

#endif