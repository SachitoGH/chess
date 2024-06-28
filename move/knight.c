#include "chess.h"

int knight(t_piece p, int from[2], int to[2])
{
    int dist_x;
    int dist_y;

    dist_x = to[1] - from[1];
    dist_y = to[0] - from[0];
    if ((abs(dist_x) == 1 && abs(dist_y) == 2) || (abs(dist_x) == 2 && abs(dist_y) == 1))
        if (!board[to[0]][to[1]].piece.name || board[to[0]][to[1]].piece.team != p.team)
          return (0);
    return (1);
}