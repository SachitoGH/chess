NAME        = chess

MAIN        = main.c

MOVE		= move/move.c \
			  move/castling.c \
			  move/legal.c \
			  move/promotion.c

PIECES		= pieces/pawn.c \
			  pieces/bishop.c \
			  pieces/knight.c \
			  pieces/rook.c \
			  pieces/queen.c \
			  pieces/king.c

UTILS		= utils/command.c \
			  utils/conversion.c \
			  utils/utils.c

STOCKFISH	= stockfish/random.c \
			  stockfish/minimax.c \
			  stockfish/evaluation.c

OBJS        = $(MAIN:.c=.o) $(MOVE:.c=.o) $(UTILS:.c=.o) $(PIECES:.c=.o) $(STOCKFISH:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Wextra -g

INC         = -I./inc/

all:        $(OBJS) $(NAME)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $(INC) $< -o $(<:.c=.o)
	@echo "Compiling OK!"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "Executable created!"

clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJS)
	@echo "Cleaned up!"

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@echo "Removed!"

re: fclean all

.PHONY: all clean fclean re
