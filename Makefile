NAME = lem-in
CC = gcc

SRC = lem_in.c lem_in_validation.c lem_in_algo.c lem_in_print.c lem_in_gnl.c bonus_colors.c validation_add_fts.c algo_add_fts.c bonus_output.c

OBJ = $(SRC:.c=.o)
CFLAGS = -c #-Wall -Wextra -Werror
HEADER = lem_in.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(OBJ) -L./libft -lft -o $(NAME)
	@echo "\033[0;37mLem-in is compiled\033[0m"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $<

clean:
	@make clean -C libft
	@make clean -C bonus
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@make fclean -C bonus
	@rm -rf $(NAME)

re: fclean all
