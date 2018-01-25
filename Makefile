# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 11:17:10 by skushnir          #+#    #+#              #
#    Updated: 2018/01/25 10:13:37 by skushnir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC =  fractol.c utility.c mandelbrot.c julia.c tree.c square.c leaf.c \
	   triangle.c triangle2.c manage_menu.c star.c opencl.c

HDR = fractol.h

LIB = libft/libft.a minilibx/libmlx.a

OBJ = $(SRC:.c=.o)

all:lib $(NAME)

$(NAME): $(OBJ) $(HDR) $(LIB)
	gcc -Wall -Wextra -Werror -O3 -o $(NAME) $(OBJ) $(LIB) -framework OpenGl -framework AppKit -framework opencl

.c.o:
	gcc  -Wall -Wextra -Werror  -O3 -c $< 

lib: 
	make -C libft;
clean:
	@make -C libft clean;
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean;
	@rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re