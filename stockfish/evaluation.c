#include "chess.h"

int get_piece_value(char piece) 
{
    switch (piece) 
    {
        case 'p': return 100;
        case 'n': return 320;
        case 'b': return 330;
        case 'r': return 500;
        case 'q': return 900;
        case 'k': return 20000; // Typically, the king is invaluable, but for scoring purposes, it can be 0
        default:  return 0;
    }
}

int piece_square_value(char piece, int x, int y) 
{
    int pawn_value[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {50, 50, 50, 50, 50, 50, 50, 50},
        {10, 10, 20, 30, 30, 20, 10, 10},
        {5, 5, 10, 25, 25, 10, 5, 5},
        {0, 0, 0, 20, 20, 0, 0, 0},
        {5, -5, -10, 0, 0, -10, -5, 5},
        {5, 10, 10, -20, -20, 10, 10, 5},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    int knight_value[8][8] = {
        {-50, -40, -30, -30, -30, -30, -40, -50},
        {-40, -20, 0, 0, 0, 0, -20, -40},
        {-30, 0, 10, 15, 15, 10, 0, -30},
        {-30, 5, 15, 20, 20, 15, 5, -30},
        {-30, 0, 15, 20, 20, 15, 0, -30},
        {-30, 5, 10, 15, 15, 10, 5, -30},
        {-40, -20, 0, 5, 5, 0, -20, -40},
        {-50, -40, -30, -30, -30, -30, -40, -50}
    };
    int bishop_value[8][8] = {
        {-20, -10, -10, -10, -10, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 10, 10, 5, 0, -10},
        {-10, 5, 5, 10, 10, 5, 5, -10},
        {-10, 0, 10, 10, 10, 10, 0, -10},
        {-10, 10, 10, 10, 10, 10, 10, -10},
        {-10, 5, 0, 0, 0, 0, 5, -10},
        {-20, -10, -10, -10, -10, -10, -10, -20}
    };
    int rook_value[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {5, 10, 10, 10, 10, 10, 10, 5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {-5, 0, 0, 0, 0, 0, 0, -5},
        {0, 0, 0, 5, 5, 0, 0, 0}
    };
    int queen_value[8][8] = {
        {-20, -10, -10, -5, -5, -10, -10, -20},
        {-10, 0, 0, 0, 0, 0, 0, -10},
        {-10, 0, 5, 5, 5, 5, 0, -10},
        {-5, 0, 5, 5, 5, 5, 0, -5},
        {0, 0, 5, 5, 5, 5, 0, -5},
        {-10, 5, 5, 5, 5, 5, 0, -10},
        {-10, 0, 5, 0, 0, 0, 0, -10},
        {-20, -10, -10, -5, -5, -10, -10, -20}
    };
    int king_value[8][8] = {
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-30, -40, -40, -50, -50, -40, -40, -30},
        {-20, -30, -30, -40, -40, -30, -30, -20},
        {-10, -20, -20, -20, -20, -20, -20, -10},
        {20, 20, 0, 0, 0, 0, 20, 20},
        {20, 30, 10, 0, 0, 10, 30, 20}
    };

    switch (piece) 
    {
        case 'p': return pawn_value[x][y];
        case 'n': return knight_value[x][y];
        case 'b': return bishop_value[x][y];
        case 'r': return rook_value[x][y];
        case 'q': return queen_value[x][y];
        case 'k': return king_value[x][y];
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
                score += get_piece_value(board[i][j].piece.name) + piece_square_value(board[i][j].piece.name, i, j);
            if (board[i][j].piece.team == 'b')
                score -= get_piece_value(board[i][j].piece.name) + piece_square_value(board[i][j].piece.name, 7 - i, j);
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
            if (board[i][j].piece.team == data.player)
                score += get_piece_value(board[i][j].piece.name);
            else if (board[i][j].piece.team != data.player && board[i][j].piece.team != 0)
                score -= get_piece_value(board[i][j].piece.name);
            j++;
        }
        i++;
    }
    return (score);
}