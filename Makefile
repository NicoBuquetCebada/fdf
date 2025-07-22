NAME = fdf

SRCS =	$(shell find ./src -iname "*.c")
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast

LIBMLX	:= ./lib/MLX42
LIBFTDIR = ./lib/libft

HEADERS	:=	-I $(LIBMLX)/include \
		 	-I $(LIBFTDIR)

LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
LIBFT = $(LIBFTDIR)/libft.a

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFTDIR) clean


fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx