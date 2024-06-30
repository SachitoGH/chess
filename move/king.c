#include "chess.h"

int king(t_piece p, t_move move)
{
    int dist_x;
    int dist_y;

    dist_x = move.to[1] - move.from[1];
    dist_y = move.to[0] - move.from[0];
    if (dist_x < -1 || dist_x > 1 || dist_y < -1 || dist_y > 1)
        return (1);
    if (!board[move.to[0]][move.to[1]].piece.name || board[move.to[0]][move.to[1]].piece.team != p.team)
        return (0);
    return (1);
}