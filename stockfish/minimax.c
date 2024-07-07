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

// int negaMax(int depth) 
// {
// 	t_move moves[218];
//     t_square temp_board[8][8];
//     char player_save;
// 	int score;
// 	int num_moves;
// 	int max = -INT_MAX;

// 	change_player();
//     if (depth == 0) 
// 		return evaluation_current();
// 	clone_board(temp_board, 0);
//     player_save = player;
// 	num_moves = generate_legal_move(moves);
//     for (int i = 0; i < num_moves; i++)  
// 	{
// 		do_move(moves[i]);
//         score = -negaMax(depth - 1);
//         player = player_save;
// 		clone_board(temp_board, 1);
//         if(score > max)
//             max = score;
//     }
//     return (max);
// }

int minimax(int depth, int is_maximizing, int alpha, int beta) 
{
    t_square temp_board[8][8];
    t_move moves[218];
    t_data tmp;
    int num_moves;

    if (depth == 0) 
	{
        return evaluation();
    }

    num_moves = generate_legal_move(moves);
    clone_board(temp_board, 0);
    save_data(&tmp, 0);
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
            save_data(&tmp, 1);
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
            save_data(&tmp, 1);
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
    t_data tmp;
    t_square temp_board[8][8];
    t_move best_move;
    int move_value;
    int best_value;
	int	count;

	count = 0;

    t_move moves[218];
    clone_board(temp_board, 0);
    save_data(&tmp, 0);
    int num_moves = generate_legal_move(moves);

    if (data.player == 'w')
        best_value = INT_MIN;
    else
        best_value = INT_MAX;

    for (int i = 0; i < num_moves; i++) 
    {
        do_move(moves[i]);
        move_value = minimax(depth - 1, change_player(), INT_MIN, INT_MAX);
        if ((move_value > best_value && tmp.player == 'w') || (move_value < best_value && tmp.player == 'b'))
        {
            best_value = move_value;
            best_move = moves[i];
			count++;
        }
        clone_board(temp_board, 1); // Restore board
        save_data(&tmp, 1);
    }
    printf("value: %d\n", best_value);
    if (count)
		*move = best_move;
    else
		*move = moves[0];
	return (0);
}

int	get_ai_move(t_move *move)
{
	find_best_move(move, 4);
    printf("AI move: %c%d -> %c%d\n", move->from[1] + 'a', 8 - move->from[0], move->to[1] + 'a', 8 - move->to[0]);
    return (0);
}