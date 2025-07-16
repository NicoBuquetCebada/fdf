NAME = fdf

SRCS =	$(shell find ./src -iname "*.c")
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wunreachable-code -Ofast

LIBMLX	:= ./lib/MLX42
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

LIBFTDIR = ./src/libft
LIBFT = $(LIBFTDIR)/libft.a

all: libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(LIBFT)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build


fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx