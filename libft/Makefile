CC = gcc
#FLAGS = -Wall -Wextra -ggdb -fsanitize=address
#FLAGS = -Wall -Wextra -Werror -Ofast
FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC =	src/ft_printf/ft_printf.c\
		src/ft_printf/ft_sprintf.c\
		src/ft_printf/ft_dprintf.c\
		src/ft_printf/extract_specifier.c\
		src/ft_printf/conv.c\
		src/ft_printf/c_conv.c\
		src/ft_printf/s_conv.c\
		src/ft_printf/d_conv.c\
		src/ft_printf/oux_conv.c\
		src/ft_printf/bin_conv.c\
		src/ft_printf/undefined_conv.c\
		src/ft_printf/tools.c\
		src/ft_printf/str_tools.c\
		src/ft_printf/write.c\
		src/ft_printf/put_buffer.c\
		src/ft_printf/malloc.c\
		src/ft_printf/utf_32_to_8.c\
		src/ft_memalloc.c\
		src/ft_memcpy.c\
		src/ft_strcpy.c\
		src/ft_strncpy.c\
		src/ft_strcat.c\
		src/ft_strchr.c\
		src/get_next_line.c\
		src/ft_strdup.c\
		src/ft_strsplit.c\
		src/malloc_free_tools.c\
		src/ft_strcmp.c\
		src/ft_strncmp.c\
		src/ft_toupper.c\
		src/ft_atoi.c\
		src/rm_begin_whitespace.c\
		src/rm_multi_whitespace.c\
		src/print_memory.c\
		src/print_hexa.c\
		src/bswap.c\
		src/ft_read.c\
		src/ft_rand.c\
		src/putchar.c\
		src/varint/v_tools.c\
		src/varint/v_check.c\
		src/varint/v_cmp.c\
		src/varint/v_add_sub.c\
		src/varint/v_mul_exp.c\
		src/varint/v_div_mod.c\
		src/varint/v_expmod.c\
		src/varint/v_gcd_eea.c\
		src/varint/v_crt.c\

OBJ = $(SRC:.c=.o)
INCLUDE = ./include/

all: $(NAME)

$(NAME): $(OBJ)
	ar -r $(NAME) $^

%.o: %.c
	$(CC) -o $@ -c $< -I $(INCLUDE) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
