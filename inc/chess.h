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

extern int	move_count;

extern t_square	board[8][8];

// main.c
int	update_board(int from[2], int to[2]);
int	print_board(void);
int	verif_input(char *str1, char *str2);


// move
// move.c
int	is_legal_move(int from[2], int to[2]);
int	do_move(char *str1, char *str2);

// pawn.c
int	pawn(t_piece p, int from[2], int to[2]);

// bishop.c
int	move_diag(t_piece p, int from[2], int dist_x, int dist_y);
int	bishop(t_piece p, int from[2], int to[2]);

// rook.c
int	move_straight(t_piece p, int from[2], int dist_x, int dist_y);
int	rook(t_piece p, int from[2], int to[2]);

// queen.c
int queen(t_piece p, int from[2], int to[2]);

// king.c
int king(t_piece p, int from[2], int to[2]);

// utils
int	convert_coord(char *str1, char *str2, int from[2], int to[2]);
char    *color(char *name);

#endif