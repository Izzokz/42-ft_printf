NAME = libftprintf.a

MAINDIR = 000_MAIN/
UTILDIR = 100_UTILS/
WRITEDIR = 101_WRITE_FORMAT/
ARRAYDIR = 102_ARRAY_PROCESS/

MAINSRC = $(MAINDIR)ft_process.c \
	$(MAINDIR)ft_printf.c
UTILSSRC = $(UTILDIR)ft_getbase.c \
	$(UTILDIR)ft_calloc.c \
	$(UTILDIR)ft_putchar_fd.c \
	$(UTILDIR)ft_putstr_fd.c \
	$(UTILDIR)ft_strlen.c \
	$(UTILDIR)ft_itoa.c \
	$(UTILDIR)ft_strdup.c \
	$(UTILDIR)ft_pow.c
WRITESRC = $(WRITEDIR)ft_write_d.c \
	$(WRITEDIR)ft_write_s.c \
	$(WRITEDIR)ft_write_b.c
ARRAYSRC = $(ARRAYDIR)ft_write_all.c \
	$(ARRAYDIR)ft_process_all.c

OBJDIR = 666_OBJ/
OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(MAINSRC) $(UTILSSRC) $(WRITESRC) $(ARRAYSRC)))

CCA = cc -Wall -Wextra -Werror -g3

TEST = ft_printf.test
TESTMAIN = main.c
TESTMAINO = $(OBJDIR)$(TESTMAIN:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)

test: $(NAME) $(TESTMAINO)
		$(CCA) -o $(TEST) $(TESTMAINO) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(MAINDIR)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

$(OBJDIR)%.o: $(UTILDIR)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

$(OBJDIR)%.o: $(WRITEDIR)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

$(OBJDIR)%.o: $(ARRAYDIR)%.c | $(OBJDIR)
	$(CCA) -o $@ -c $<

$(TESTMAINO): $(TESTMAIN)
	$(CCA) -o $@ -c $<

clean:
		rm -f $(OBJ) $(TESTMAINO)

fclean: clean
		rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test
