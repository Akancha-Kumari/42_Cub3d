# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/28 16:53:13 by ji-hong           #+#    #+#              #
#    Updated: 2025/08/28 19:03:44 by ji-hong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SRCS = arena/arena.c get_next_line/get_next_line.c \
       src/parse/parse_map.c src/parse/parse_read.c src/parse/parse_texture.c \
       src/parse/parse_util.c \
       src/main.c src/error.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS): %.o: %.c include/cub3d.h include/parse.h arena/arena.h \
	get_next_line/get_next_line.h
	$(CC) $(FLAGS) -c $< -o $@

libft/libft.a:
	cd libft && make

clean:
	$(RM) $(OBJS)
	cd libft && make clean

fclean: clean
	$(RM) $(NAME)
	cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re

