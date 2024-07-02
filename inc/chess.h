#ifndef CHESS_H
# define CHESS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

# define WHITE_BG "white"
# define BLACK_BG "black"
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


// global var;
extern int		check;
extern int		move_count;
extern t_square	board[8][8];
extern char		player;
extern	t_move	last_move;
extern t_piece	piece_taken;

// main.c
int	update_board(t_move move);
void	print_board(void);
void	print_board_colored(void);
int	verif_input(char *move);

// utils
// command.c
int	special_command(char *input);

// move
// move.c
int	is_legal_move(t_move move);
int	undo_move(t_move move);
int	do_move(t_move move);
int	my_piece_is_attacked(int pos_x, int pos_y);
void	change_player(void);
int	locate_king(char team, int king_pos[2]);
int king_under_attack(void);

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

// castling.c
int	castling(char *san, char **move);

// conversion.c
char	*san_to_coord(char *move_str);
int	str_to_move(char *move_str, t_move *move);
int	convert_coord(char *move_str, t_move *move);

// utils.c
char    *color(char *name);
char    *color_bg(char *name);
int inside_board(char letter, char number);
int is_piece(char p);

#endif