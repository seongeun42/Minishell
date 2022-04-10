# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongele <seongele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/14 06:24:59 by sujo              #+#    #+#              #
#    Updated: 2022/04/10 14:04:03 by seongele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRC_DIR = ./src/
SRCS = src/main.c\
		src/utils.c

CMD_DIR = ./src/cmd/
CMDS = src/cmd/cd.c\
		src/cmd/echo.c\
		src/cmd/env.c\
		src/cmd/export.c\
		src/cmd/pwd.c\
		src/cmd/unset.c\
		src/cmd/exit.c

ENV_DIR = ./src/envp/
ENVS = src/envp/env_split.c\
		src/envp/env_parsing.c\
		src/envp/env_func.c\
		src/envp/env_insert.c\
		src/envp/env_get.c

PARSE_DIR = ./src/parse/
PARS = src/parse/parsing.c\
		src/parse/redirect.c\
		src/parse/line_split.c\
		src/parse/make_node.c\
		src/parse/make_cmd_array_list.c\
		src/parse/make_redirect_list.c

PROCESS_DIR = ./src/process/
PROCS = src/process/process.c\
		src/process/exec_redirect.c\
		src/process/exec_command.c\
		src/process/process_utils.c

SIG_DIR = ./src/signal/
SIGS = src/signal/signal.c\
		src/signal/signal_child.c\
		src/signal/signal_parent.c

OBJS = $(SRCS:.c=.o) $(ENVS:.c=.o) $(PARS:.c=.o) $(CMDS:.c=.o) $(PROCS:.c=.o) $(SIGS:.c=.o)
NAME = minishell
HEADER = -I include/
CFLAG = -Wall -Werror -Wextra
#CFLAG = -fsanitize=address
LIBFT_DIR = ./libft
LIBFT_NAME = libft.a

# ============ color==============
FG_YELLOW	=\e[33m
FG_RED		=\e[31m
FG_GREEN	=\e[32m
FG_BLUE		=\e[34m
FG_MAGENTA	=\e[35m
FG_CYAN		=\e[36m
FG_BRIGHT_Y	=\e[93m
NO_COLOR	=\e[0m
LF = \e[1K\r$(NO_COLOR)
# ================================

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJS)
	@$(CC) $(CFLAG) -L. -lft -o $@ $(OBJS) -lreadline $(LDFLAGS)
	@printf "$(LF)$(FG_GREEN)Minishell complete\n$(NO_COLOR)"

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)
	@mv $(LIBFT_DIR)/$(LIBFT_NAME) .

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER) $(CPPFLAGS)
	@printf "$(LF)🔨 $(FG_MAGENTA)minishell 만드는 중 $(FG_CYAN)%-33.33s" $@

$(ENV_DIR)%.o: $(ENV_DIR)%.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

$(CMD_DIR)%.o: $(CMD_DIR)%.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

$(PARSE_DIR)%.o: $(PARSE_DIR)%.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

$(SIG_DIR)%.o: $(SIG_DIR)%.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@printf "clean\n"

fclean: clean
	@rm -f $(NAME) $(LIBFT_NAME)
	@make fclean -C $(LIBFT_DIR)
	@printf "fclean\n"

re: fclean all

.PHONY: all clean fclean re
