#include "chess.h"

int queen(t_piece p, int from[2], int to[2])
{
    int dist_x;
    int dist_y;

    dist_x = to[1] - from[1];
    dist_y = to[0] - from[0];
    if (dist_x == 0 && dist_y == 0)
        return (1);
    if (abs(dist_x) == abs(dist_y))
    {
        if (!move_diag(p, from, dist_x, dist_y))
            return (0);
    }
    if ((dist_x && !dist_y) || (dist_y && !dist_x))
    {
        if (!move_straight(p, from, dist_x, dist_y))
            return (0);
    }
    return (1);
}