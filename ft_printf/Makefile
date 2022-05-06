NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -c
ARCHIVE = ar -crs
SRCS = ft_putchar.c	\
		ft_putstr.c \
 		ft_putnbr.c \
		ft_putnbr_u.c \
	 	to_hex_lower.c \
		to_hex_upper.c \
		print_ptr.c \
		ft_printf.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(ARCHIVE) $(NAME) $(OBJS) 

$(OBJS):
	$(CC) $(CFLAGS) $(SRCS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
