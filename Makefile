##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Compile cod executable
##

SRC =   main.c \
		error_handler.c \
		window.c \
		my_strdup.c

OBJ = $(SRC:.c=.o)

NAME = cod

all: $(NAME)

$(NAME): $(OBJ)
	clang $(OBJ) -o $(NAME) -Iinclude -lncurses

%.o: %.c
	clang -g3  -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f *.gcda *.gcno *.pch

fclean: clean
	rm -f $(NAME)

re: fclean all
