NAME = libftprintf.a
SRC = ft_getbase.c \
	ft_write_d.c \
	ft_write_s.c \
	ft_write_b.c \
	ft_process.c \
	ft_printf.c \
	ft_calloc.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_strlen.c \
	ft_itoa.c \
	ft_strdup.c \
	ft_pow.c
OBJ = $(SRC:.c=.o)

CCA = cc -Wall -Wextra -Werror -g3

TEST = ft_printf.test
TESTMAIN = main.c
TESTMAINO = $(TESTMAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)

test: $(NAME) $(TESTMAINO)
		$(CCA) -o $(TEST) $(TESTMAINO) $(OBJ)

%.o: %.c
		$(CCA) -o $@ -c $^

clean:
		rm -f $(OBJ) $(TESTMAINO)

fclean: clean
		rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test
