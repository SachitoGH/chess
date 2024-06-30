#include "chess.h"

int knight(t_piece p, t_move move)
{
    int dist_x;
    int dist_y;

    dist_x = move.to[1] - move.from[1];
    dist_y = move.to[0] - move.from[0];
    if ((abs(dist_x) == 1 && abs(dist_y) == 2) || (abs(dist_x) == 2 && abs(dist_y) == 1))
        if (!board[move.to[0]][move.to[1]].piece.name || board[move.to[0]][move.to[1]].piece.team != p.team)
          return (0);
    return (1);
}