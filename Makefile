NAME = pipex
CC = cc 
CFLAGS = -c #-Wall -Wextra -Werror
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

%.c:
	$(CC) $(CFLAGS) $(SRCS)

all: compile_printf $(NAME)

compile_printf:
	cd ft_printf && make

$(NAME): $(OBJS)
	$(CC) $(OBJS) -lftprintf -L ft_printf -o $(NAME)

clean:
	rm -f *.o ft_printf/*.o

fclean: clean
	rm -f $(NAME) ft_printf/libftprintf.a

re: fclean all

.PHONY: all clean fclean re compile_printf
