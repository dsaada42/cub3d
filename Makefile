# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsaada <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 15:22:57 by dsaada            #+#    #+#              #
#    Updated: 2021/10/20 22:25:11 by dsaada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = gcc

DEBUG = -g3 -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c\
      src/drawing.c\
      src/bresenham.c\
      src/get_next_line.c\
      src/get_next_line_utils.c\
      src/get_dist.c\
      src/parser.c\
      src/parse_sprites.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	cd ./libft && make
	$(CC) $(OBJ) $(DEBUG) -lm -lX11 -lXext ./mlx_linux/libmlx.a ./libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	rm -f src/*.o
	cd ./libft && make clean

fclean: clean
	rm -f $(NAME)
	cd ./libft && make fclean

re: fclean all

.PHONY: all $(NAME) clean fclean re
