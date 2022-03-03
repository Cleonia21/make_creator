# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Cleonia <1-d_x_d-1@mail.ru>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 13:14:01 by Cleonia           #+#    #+#              #
#    Updated: 2022/03/03 13:14:08 by Cleonia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	make_creator

CPP		=	c++ -Wall -Wextra -Werror -std=c++98
SRCS	=	make_creator.cpp
OBJ		=	$(SRCS:.cpp=.o)

all		:	$(NAME)

%.o		:	%.cpp
			$(CPP) -c $< -o $@

$(NAME)	:	$(OBJ) MAKEFILE
			$(CPP) $(OBJ) -o $(NAME)

clean	:
			rm -f $(OBJ)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
