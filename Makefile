NAME        = chess

MAIN        = main.c

MOVE		= move/move.c \
			  move/pawn.c \
			  move/bishop.c \
			  move/knight.c \
			  move/rook.c \
			  move/queen.c \
			  move/king.c \
			  move/castling.c \
			  move/conversion.c \
			  move/utils.c

UTILS		= utils/command.c

OBJS        = $(MAIN:.c=.o) $(MOVE:.c=.o) $(UTILS:.c=.o)

CC          = gcc

CFLAGS      = -Wall -Wextra

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
