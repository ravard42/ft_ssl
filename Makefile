CC = gcc
NAME = ft_ssl

#FLAGS = -Wall -Wextra -Werror
#FLAGS = -Wall -Wextra -Werror -Ofast
FLAGS = -Wall -Wextra -Werror -ggdb -fsanitize=address

SRC = src/main.c\
		src/init_and_free.c\
		src/cmd_opt_parser.c\
		src/arg_parser.c\
		src/usage.c\
		src/hash/parser.c\
		src/hash/padding.c\
		src/hash/format.c\
		src/hash/md5/md5.c\
		src/hash/md5/init.c\
		src/hash/md5/func.c\
		src/hash/md5/block_hash.c\
		src/hash/sha256/sha256.c\
		src/hash/sha256/init.c\
		src/hash/sha256/func.c\
		src/hash/sha256/func_bis.c\
		src/hash/sha256/block_hash.c\
		src/sym/parser.c\
		src/sym/hstr_to_64_t.c\
		src/sym/base64/b64_block_e.c\
		src/sym/base64/b64_block_d.c\
		src/sym/base64/b64.c\
		src/sym/des/core/key_schedule.c\
		src/sym/des/core/diffusion.c\
		src/sym/des/core/confusion.c\
		src/sym/des/core/round.c\
		src/sym/des/core/des_block_e_d.c\
		src/sym/des/pbkdf/pbkdf.c\
		src/sym/des/pbkdf/hash_mode.c\
		src/sym/des/padding.c\
		src/sym/des/check.c\
		src/sym/des/opt_a.c\
		src/sym/des/des.c\
		src/sym/des/mode/ecb.c\
		src/sym/des/mode/cbc.c\
		src/sym/des/mode/ofb.c\
		src/sym/des/mode/cfb.c\
		src/sym/des/mode/ecb3.c\
		src/sym/des/mode/cbc3.c\
		src/sym/des/mode/ofb3.c\
		src/sym/des/mode/cfb3.c\
		src/asym/prob_prim_test.c\
	
OBJ = $(SRC:.c=.o)

INCL = -I libft/include -I include
LIB =  -L ./libft -lft -lm

all : $(NAME)

$(NAME) : ./libft/libft.a $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(INCL) $(LIB)

./libft/libft.a :
	make -C libft

%.o : %.c
	$(CC) -o $@ -c $< $(FLAGS) $(INCL)

clean : 
	rm -f $(OBJ)
	make -C libft fclean

fclean : clean
	rm -f $(NAME)

re : fclean $(NAME)
