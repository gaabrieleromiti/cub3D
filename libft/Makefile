# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/11 17:31:20 by gromiti           #+#    #+#              #
#    Updated: 2024/04/21 19:02:23 by gromiti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	   ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	   ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	   ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	   ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   get_next_line.c get_next_line_utils.c


OBJS = $(SRCS:%.c=%.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		ft_lstmap.c

BONUS_OBJS = $(BONUS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror
MAKEFLAGS += --silent

RM = rm -f

INC = "."
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): ${OBJS}
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

bonus: $(NAME) $(BONUS_OBJS)
	ar rc $(NAME) $(BONUS_OBJS)
	ranlib $(NAME)

all: $(NAME) $(BONUS_NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_OBJS)

re: fclean all

.PHONY: all clean fclean re .c.o
