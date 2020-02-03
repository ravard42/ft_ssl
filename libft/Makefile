CC = gcc
#FLAGS = -Wall -Wextra -Werror
FLAGS = -Wall -Wextra
#FLAGS = -Wall -Wextra -fsanitize=address -g
NAME = libft.a
SRC =	src/ft_memalloc.c\
		src/ft_memset.c\
		src/ft_memcpy.c\
		src/ft_memcmp.c\
		src/ft_putchar.c\
		src/ft_puthex.c\
		src/ft_putstr.c\
		src/ft_strlen.c\
		src/ft_strcpy.c\
		src/ft_strncpy.c\
		src/ft_strcat.c\
		src/ft_strchr.c\
		src/ft_strcmp.c\
		src/ft_strncmp.c\
		src/ft_revstr.c\
		src/ft_strdup.c\
		src/ft_strsplit.c\
		src/ft_atoi.c\
		src/ft_is_decimal.c\
		src/hstr_to_64_t.c\
		src/malloc_free_tools.c\
		src/rm_begin_whitespace.c\
		src/rm_multi_whitespace.c\
		src/get_next_line.c\
		src/ft_rand.c\
		src/ft_read.c\
		src/ft_printf/ft_printf.c\
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
		src/ft_printf/write.c\
		src/ft_printf/put_buffer.c\
		src/ft_printf/malloc.c\
		src/ft_printf/utf_32_to_8.c\
		src/bswap.c\
		src/varint/v_tools.c\
		src/varint/v_tools_2.c\
		src/varint/v_check.c\
		src/varint/v_op_check.c\
		src/varint/v_cmp.c\
		src/varint/v_add_sub.c\
		src/varint/v_mul_exp.c\
		src/varint/v_div_mod.c\
		src/varint/v_expmod.c\
		src/varint/v_gcd_eea_inv.c\
		src/varint/v_crt.c\
		src/varint/v_asn1_der_int_seq_e.c\
		src/varint/v_asn1_der_int_seq_d.c\

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
