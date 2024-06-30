#ifndef CHESS_H
# define CHESS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

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
extern int	move_count;
extern t_square	board[8][8];
extern char	player;

// main.c
int	update_board(t_move move);
int	print_board(void);
int	verif_input(char *move);


// move
// move.c
int	is_legal_move(t_move move);
int	do_move(char *move_str);

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

// notation.c
char	*san_to_coord(char *move_str);

// utils.c
int	convert_coord(char *move_str, t_move *move);
char    *color(char *name);
int inside_board(char letter, char number);
int is_piece(char p);

#endif