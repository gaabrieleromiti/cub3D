# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 12:38:11 by gromiti           #+#    #+#              #
#    Updated: 2025/04/24 16:58:25 by gromiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIBFT = libft.a

MLX = libmlx_linux.a

SRC = src/2d.c src/free.c src/init.c src/main.c src/parser.c src/window.c

OBJS = $(SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror
MLX_CFLAG = -lm -Lminilibx-linux -lmlx_Linux -lX11 -lXext
MAKEFLAGS += --silent

RM = rm -f

INC = -I./incl -I./minilibx-linux
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -L ./libft -L ./minilibx-linux -lft $(MLX_CFLAG) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	$(MAKE) -C ./minilibx-linux

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./minilibx-linux

re: clean all

.PHONY: all clean fclean re .c.oC = gcc