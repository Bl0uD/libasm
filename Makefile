NAME = libasm.a

CC = nasm
FLAGS = -f elf64 -g -F dwarf
OBJDIR = objs

SRCS_TEST = srcs/main.c					\
			srcs/test/test_ft_strcmp.c	\
			srcs/test/test_ft_strcpy.c	\
			srcs/test/test_ft_strlen.c	\
			srcs/test/test_ft_strdup.c	\
			srcs/test/test_ft_read.c	\
			srcs/test/test_ft_calloc.c	\
			srcs/test/test_ft_write.c

SRCS = srcs/ft_strcmp.s		\
		srcs/ft_strcpy.s	\
		srcs/ft_strlen.s	\
		srcs/ft_strdup.s	\
		srcs/ft_read.s		\
		srcs/ft_calloc.s	\
		srcs/ft_write.s

OBJS = $(SRCS:srcs/%.s=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: srcs/%.s
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) $< -o $@

test: $(NAME) $(SRCS_TEST)
	gcc -Wall -Wextra -Werror -z noexecstack $(SRCS_TEST) -L. -lasm -Iincludes -o test

clean:
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME) test

re : fclean all

.PHONY: all clean fclean re