NAME = lem-in
CC = gcc

SRC = lem_in.c lem_in_validation.c get_next_line.c finding_path.c lem_in_print_path.c bonus.c lem_in_path.c 

OBJ = $(SRC:.c=.o)
CFLAGS = -c 
#-Wall -Wextra -Werror
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
	@rm -rf $(OBJ)

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "Lem-in is cleaned ..."

re: fclean all
