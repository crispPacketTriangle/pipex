CC=cc -g
FLAGS=-Wall -Werror -Wextra
NAME=pipex
EXT=-L ./libft/ -lft
LOGO=~/42/fdf/logo.sh
SRCS=pipex.c pipex_utils.c ft_split_p.c
OBJS= $(SRCS:.c=.o)
LIBFT=/libft/
LFT=libft.a

all: deps $(NAME)
		@if [ -f $(LOGO) ]; then \
			bash $(LOGO); \
		fi 
deps:
		$(MAKE) -C libft

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(EXT) $(FLAGS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re deps