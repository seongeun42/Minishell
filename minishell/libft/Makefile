CC=gcc
SRCS=ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c\
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_memccpy.c\
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
	ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
	ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_calloc.c \
	ft_split.c ft_strdup.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_itoa.c\
	ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS=$(SRCS:.c=.o)
NAME=libft.a
HEADER=-I .
CFLAG=-Wall -Werror -Wextra

FG_YELLOW	=\e[33m
FG_RED		=\e[31m
FG_BLUE		=\e[34m
FG_MAGENTA	=\e[35m
FG_CYAN		=\e[36m
NO_COLOR	=\e[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rc $(NAME) $^
	@printf "$(FG_YELLOW)libft complete\n$(NO_COLOR)"

%.o: %.c
	@$(CC) $(CFLAG) -c -o $@ $< $(HEADER)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
