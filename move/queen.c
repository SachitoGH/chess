#include "chess.h"

int queen(t_piece p, t_move move)
{
    int dist_x;
    int dist_y;

    dist_x = move.to[1] - move.from[1];
    dist_y = move.to[0] - move.from[0];
    if (dist_x == 0 && dist_y == 0)
        return (1);
    if (abs(dist_x) == abs(dist_y))
    {
        if (!move_diag(p, move.from, dist_x, dist_y))
            return (0);
    }
    if ((dist_x && !dist_y) || (dist_y && !dist_x))
    {
        if (!move_straight(p, move.from, dist_x, dist_y))
            return (0);
    }
    return (1);
}