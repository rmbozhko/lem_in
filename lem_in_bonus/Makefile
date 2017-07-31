NAME = visual_out
CC = gcc

SRC = bonus_visual.c bonus_visual_err.c get_next_line.c 
OBJ = $(SRC:.c=.o)
CFLAGS = -c 
#-Wall -Wextra -Werror
HEADER = lem_in_bonus.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C ../libft
	@$(CC) $(OBJ) -L../libft -lft -o $(NAME)
	@echo "lem-in bonus is compiled"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $<

clean:
	@make clean -C ../libft
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C ../libft
	@rm -rf $(NAME)
	@echo "Cleaned ..."

re: fclean all
