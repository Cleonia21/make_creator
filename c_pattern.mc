NAME	=	

GCC		=	gcc -Wall -Wextra -Werror
SRCS	=	
OBJ		=	$(SRCS:.c=.o)

all		:	$(NAME)

%.o		:	%.c
			$(GCC) -c $< -o $@

$(NAME)	:	$(OBJ) MAKEFILE
			$(GCC) $(OBJ) -o $(NAME)

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

