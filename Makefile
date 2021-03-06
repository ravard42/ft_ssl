CC = gcc
NAME = ft_ssl

#FLAGS = -Wall -Wextra -g -fsanitize=address
FLAGS = -Wall -Wextra -Werror -O2

SRC = src/main.c\
		src/g_ssl_str.c\
		src/init.c\
		src/free.c\
		src/parser/cmd_parser.c\
		src/parser/opt_parser.c\
		src/parser/arg_parser.c\
		src/hash/hash_parser.c\
		src/hash/hash_padding.c\
		src/hash/format.c\
		src/hash/shift_rot.c\
		src/hash/md5/md5.c\
		src/hash/md5/init.c\
		src/hash/md5/func.c\
		src/hash/md5/block_hash.c\
		src/hash/sha256/sha256.c\
		src/hash/sha256/init.c\
		src/hash/sha256/func.c\
		src/hash/sha256/func_bis.c\
		src/hash/sha256/block_hash.c\
		src/sym/sym_parser.c\
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
		src/sym/des/des_padding.c\
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
		src/asym/genrsa/genrsa_parser.c\
		src/asym/genrsa/sieve.c\
		src/asym/genrsa/prob_prime_test.c\
		src/asym/genrsa/genrsa.c\
		src/asym/rsa/rsa_parser.c\
		src/asym/rsa/read_rsak.c\
		src/asym/rsa/rsa_des_opt.c\
		src/asym/rsa/write_rsak.c\
		src/asym/rsa/rsa.c\
		src/asym/rsautl/rsautl_parser.c\
		src/asym/rsautl/rsautl.c\
		src/asym/rsautl/cra.c\
		src/csprng.c\
		src/crypta/crypta_parser.c\
		src/crypta/break_des_ecb.c\
	
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
