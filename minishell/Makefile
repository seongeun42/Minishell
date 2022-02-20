# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongele <seongele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 06:24:59 by sujo              #+#    #+#              #
#    Updated: 2022/02/20 18:05:57 by seongele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
SRC_DIR=./src/
SRCS=src/main.c\
	src/utils.c

ENV_DIR=./src/envp/
ENVS=src/envp/env_split.c\
	src/envp/env_parsing.c\
	src/envp/env_func.c\
	src/envp/env_insert.c

PARSE_DIR=./src/parse/
PARS=src/parse/parsing.c\
	src/parse/redirect.c\
	src/parse/line_split.c\
	src/parse/make_node.c

OBJS=$(SRCS:.c=.o) $(ENVS:.c=.o) $(PARS:.c=.o)
NAME=minishell
HEADER=-I include/
#CFLAG=-Wall -Werror -Wextra
CFLAG=-fsanitize=address
LIBFT_DIR=./libft
LIBFT_NAME=libft.a


all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJS)
	$(CC) $(CFLAG) -L. -lft -o $@ $(OBJS) -lreadline

$(LIBFT_NAME):
	make -C $(LIBFT_DIR)
	mv $(LIBFT_DIR)/$(LIBFT_NAME) .

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

$(ENV_DIR)%.o: $(ENV_DIR)%.c
	$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

$(PARSE_DIR)%.o: $(PARSE_DIR)%.c
	$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
