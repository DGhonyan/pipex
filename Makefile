NAME = pipex
CC = cc -Wall -Wextra -Werror
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: compile_printf $(NAME)

compile_printf:
	cd ft_printf && make

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lftprintf -L ft_printf -o $(NAME)

$(OBJS):
	$(CC) -c $(SRCS)
clean:
	rm -f *.o ft_printf/*.o

fclean: clean
	rm -f $(NAME) ft_printf/libftprintf.a

re: fclean all

PHONY: all clean fclean re
