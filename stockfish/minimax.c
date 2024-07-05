#include "chess.h"

int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int minimax(int depth, int is_maximizing, int alpha, int beta) 
{
    t_square temp_board[8][8];
    t_move moves[218];
    int num_moves;
	char	save_player;

    if (depth == 0) 
	{
        return evaluation();
    }

    num_moves = generate_legal_move(moves);
    clone_board(temp_board, 0);
	save_player = player;
    if (is_maximizing) 
	{
        int max_eval = INT_MIN;
		for (int i = 0; i < num_moves; i++) 
		{
            do_move(moves[i]);
            int eval = minimax(depth - 1, change_player(), alpha, beta); // Change to minimizing player
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            clone_board(temp_board, 1); // Restore board
			player = save_player; // restore player
            if (beta <= alpha) 
			{
                break; // Alpha-beta pruning
            }
        }
        return max_eval;
    }
	else 
	{
        int min_eval = INT_MAX;
		for (int i = 0; i < num_moves; i++) 
		{
            do_move(moves[i]);
            int eval = minimax(depth - 1, change_player(), alpha, beta); // Change to maximizing player
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            clone_board(temp_board, 1); // Restore board
			player = save_player;
            if (beta <= alpha) 
			{
                break; // Alpha-beta pruning
            }
        }
        return min_eval;
    }
}

int find_best_move(t_move *move, int depth) 
{
    char player_save;
    t_square temp_board[8][8];
    t_move best_move;
    int move_value;
    int best_value;

    player_save = player;
    clone_board(temp_board, 0);
    t_move moves[218];
    int num_moves = generate_legal_move(moves);

    if (player_save == 'w') 
	{
        best_value = INT_MIN;
        for (int i = 0; i < num_moves; i++) 
		{
            do_move(moves[i]);
            move_value = minimax(depth - 1, change_player(), INT_MIN, INT_MAX);
            if (move_value > best_value) 
			{
                best_value = move_value;
                best_move = moves[i];
            }
			player = player_save;
            clone_board(temp_board, 1); // Restore board
        }
    } 
	else 
	{
        best_value = INT_MAX;
        for (int i = 0; i < num_moves; i++) 
		{
            do_move(moves[i]);
            move_value = minimax(depth - 1, change_player(), INT_MIN, INT_MAX);
            if (move_value < best_value) 
			{
				printf("move_value: %d\n", move_value);
				printf("best_value: %d\n", best_value);
				printf("move: %i %i %i %i\n", moves[i].from[0], moves[i].from[1], moves[i].to[0], moves[i].to[1]);
                best_value = move_value;
                best_move = moves[i];
            }
			player = player_save;
            clone_board(temp_board, 1); // Restore board
        }
    }

    player = player_save;
    *move = best_move;
    return 0;
}

int negaMax(int depth) 
{
	t_move moves[218];
    t_square temp_board[8][8];
	int score;
	int num_moves;
	int max = -INT_MAX;

	change_player();
    if (depth == 0) 
		return evaluation_current();
	clone_board(temp_board, 0);
	num_moves = generate_legal_move(moves);
    for (int i = 0; i < num_moves; i++)  
	{
		do_move(moves[i]);
        score = -negaMax(depth - 1);
		change_player();
		clone_board(temp_board, 1);
        if(score > max)
            max = score;
    }
    return max;
}

int	get_ai_move(t_move *move)
{
	find_best_move(move, 2);
	return (0);
}