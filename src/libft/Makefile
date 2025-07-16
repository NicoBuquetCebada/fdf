NAME = libft.a
SRCS =	ft_arrlen.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_split.c\
		ft_strdup.c\
		ft_strlcat.c\
		ft_strlen.c\
		ft_substr.c\
		ft_atoi.c\
		ft_strncmp.c

OBJS = $(SRCS:.c=.o)
INCL = libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS) $(INCL)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
