#include "chess.h"

int get_piece_value(char piece) 
{
    switch (piece) 
    {
        case 'p': return 1;
        case 'n': return 3;
        case 'b': return 3;
        case 'r': return 5;
        case 'q': return 9;
        case 'k': return 0; // Typically, the king is invaluable, but for scoring purposes, it can be 0
        default:  return 0;
    }
}

int evaluation(void)
{
    int score;
    int i;
    int j;

    score = 0;
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].piece.team == 'w')
                score += get_piece_value(board[i][j].piece.name);
            if (board[i][j].piece.team == 'b')
                score -= get_piece_value(board[i][j].piece.name);
            j++;
        }
        i++;
    }
    return (score);
}

int evaluation_current(void)
{
    int score;
    int i;
    int j;

    score = 0;
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (board[i][j].piece.team == player)
                score += get_piece_value(board[i][j].piece.name);
            else if (board[i][j].piece.team != player && board[i][j].piece.team != 0)
                score -= get_piece_value(board[i][j].piece.name);
            j++;
        }
        i++;
    }
    return (score);
}