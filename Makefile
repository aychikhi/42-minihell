NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = ./utils/ft_split.c ./utils/ft_strlen.c ./utils/ft_strdup.c ./utils/ft_isalnum.c ./utils/ft_isalpha.c ./utils/ft_isdigit.c ./utils/ft_itoa.c ./utils/ft_lstnew.c\
		./utils/ft_strncmp.c ./utils/ft_strcmp.c ./utils/ft_strcpy.c ./utils/ft_strchr.c ./utils/ft_substr.c ./utils/ft_lstadd_back.c\
		./token/helper.c ./token/helper1.c ./token/helper2.c ./token/helper3.c ./token/tokeniser.c checker_fun.c main.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) minishell.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean