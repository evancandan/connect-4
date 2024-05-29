SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

NAME	=	connect-four

CFLAGS	+=	-g -W -Wall -Wextra -Werror -lncurses

all:$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re