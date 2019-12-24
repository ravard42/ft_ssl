/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:58:03 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 12:27:35 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "commands.h"
# include "b64_tabs.h"
# include "des/key_perm.h"
# include "des/perm.h"
# include "des/s_box.h"

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31;1m"
# define KGRN  "\x1B[32;1m"
# define KYEL  "\x1B[33;1m"
# define KBLU  "\x1B[34;1m"
# define KMAG  "\x1B[35;1m"
# define KCYN  "\x1B[36;1m"
# define KWHT  "\x1B[37;1m"

# define U "%susage%s: ./ft_ssl %scommand %s[opts]%s [args]\n"
# define P "-p, echo STDIN to STDOUT and append the checksum to STDOUT"
# define Q "-q, quiet mode, only print the checksum"
# define R "-r, reverse the format of the output"
# define S "-s, print the sum of the given string"
# define E "-e, encode/encrypt mode (default)"
# define D "-d, decode/decrypt mode"
# define I "-i, input file for message"
# define O "-o, output file for message"
# define DES_ONLY "\x1B[33;1mdes only:\x1B[0m"
# define A " -a, decode/encode the input/output in base64"

# define K " -k, key in hexa is the next argument."
# define V " -v, initialization vector in hexa is the next argument."
# define SALT " -s, the salt in hexa is the next argument."
# define PW " -p, password in ascii is the next argument."

# define SH_L(x, n) ((x) << (n))
# define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define SH_R(x, n) ((x) >> (n))
# define ROT_R(x, n) (((x) >> (n)) | ((x) << (32-(n))))

# define ROT_28_LEFT(x, n) (((x)<<(n)) | ((x)>>(28-(n)))) & 0xfffffff000000000

typedef struct			s_write
{
	int				fd;
	char			*msg;
	int64_t			len;
}						t_write;

/*
**NB: t_write is used for padding with hash commands
**		and for -a option with sym cipher commands
*/

typedef struct			s_hash
{
	uint32_t		s[64];
	uint32_t		k[64];
	uint32_t		h[8];
	bool			pbkdf;
}						t_hash;

typedef struct			s_arg
{
	uint64_t		x[3];
	char			*p;
	bool			set;
}						t_arg;

typedef struct			s_sym
{
	uint32_t		r;
	uint32_t		l;
	t_arg			arg[4];
	uint64_t		sub_k[48];
	uint8_t			id_k;
}						t_sym;

/*
** NOTE attributs  t_arg
** arg[0] : k
** arg[1] : v
** arg[2] : s
** arg[3] : p
*/

typedef struct			s_parse
{
	t_cmd			cmd;
	uint8_t			i[3];
	uint8_t			o[14];
	char			*in_file;
	char			*out_file;
	t_read			r;
	t_write			w;
	t_hash			h;
	t_sym			s;
}						t_parse;

/*
** NOTE attributs  t_parse
**
** i[0] indice de l'argument en cours de traitement
** i[1] == 1 <-> on a déjà lu sur stdin (hash only)
**	i[1] == 2 <-> file to be decrypt salted (sym only)
** i[2] nombre de print sur stdout (hash only)
**
** o[0] = 1 => traitement des opts désactivés
** o[1] : -p on/off
** o[2] : -q on/off
** o[3] : -r on/off
** o[4] : -s on/off
** o[5] : -e on/off
** o[6] : -d on/off
** o[7] : -i on/off
** o[8] : -o on/off
** o[9] : -a on/off
** o[10] : -k on/off
** o[11] : -v on/off
** o[12] : -s on/off
** o[13] : -p on/off
*/

/*
**src
*/
int						usage(void);
void					init_parse_struct(t_parse *p);
void					free_parse_struct(t_parse *p);
uint32_t				*multi_bswap32(uint32_t *h, int64_t size);
int						cmd_parser(char *arg, t_parse *p);
int						opt_parser(char *arg, t_parse *p);
int						str_parser(char *arg, t_parse *p);
int						fd_parser(char *arg, t_parse *p);
/*
**src/hash
*/
char					*hash_padding(t_parse *p);
int						hash_parser(int argc, char **argv, t_parse *p);
void					print_format(t_parse *p, t_hash *hash);
/*
**src/hash/md5
*/
int						md5(t_parse *p);
void					md5_init(t_hash *hash);
uint32_t				f0(uint32_t *h);
uint32_t				f1(uint32_t *h);
uint32_t				f2(uint32_t *h);
uint32_t				f3(uint32_t *h);
void					md5_block_hash(t_hash *hash, char *pad,
							int64_t *id_block);
/*
**src/hash/sha256
*/
int						sha256(t_parse *p);
void					sha256_init(t_hash *hash);
uint32_t				g0(uint32_t *h);
uint32_t				g1(uint32_t *h);
uint32_t				g2(uint32_t *h);
uint32_t				g3(uint32_t *h);
uint32_t				g4(uint32_t *h);
uint32_t				g5(uint32_t *h);
void					sha256_block_hash(t_hash *hash, char *pad,
							int64_t *id_block);
/*
**src/sym/
*/
uint64_t				*hstr_to_64_t(uint64_t *x, int64_t len_64, char *str);
void					format_key(t_parse *p);
int						sym_parser(int argc, char **argv, t_parse *p);
/*
**src/sym/base64
*/
uint32_t				be_transpo(uint32_t x);
uint32_t				b64_block_e(uint32_t in, uint8_t k, uint8_t b_endian);
void					del_whitespaces(t_read *r);
uint32_t				b64_block_d(uint32_t in, uint8_t *k, uint8_t b_endian);
int						run_b64_e(t_parse *p);
int						run_b64_d(t_parse *p);
int						b64(t_parse *p);

/*
**src/sym/des/block_cipher
*/
uint64_t				parity_bit_drop(uint64_t key);
uint64_t				compress_d_box(uint64_t x);
void					load_sub_k(t_sym *s, uint8_t id_k);
uint64_t				initial_perm(uint64_t x);
uint64_t				final_perm(uint64_t x);
uint64_t				expansion_perm(uint32_t x, char b_endian);
uint32_t				round_perm(uint32_t x);
uint32_t				s_boxes(uint64_t x);
void					des_round(t_parse *p, uint8_t i);
uint64_t				des_block_e(uint64_t x, t_parse *p);
uint64_t				des_block_d(uint64_t x, t_parse *p);
uint64_t				des_triple(uint64_t x, t_parse *p);

/*
**src/sym/des
*/
int						set_pass(t_parse *p, int verify);
int						md5_pass_salt_hash(t_parse *tmp, t_parse *p);
int						pbkdf(t_parse *p);
int						check_out(t_parse *p);
int						check_k_v(t_parse *p);
char					*des_padding(t_parse *p, int64_t q);
int64_t					des_unpadding(t_write *w);
int						opt_a_e(t_parse *p);
int						opt_a_d(t_parse *p);
int						ecb_e(t_parse *p, int64_t q);
int						ecb_d(t_parse *p, int64_t q);
int						cbc_e(t_parse *p, int64_t q);
int						cbc_d(t_parse *p, int64_t q);
int						ofb_e_d(t_parse *p, int64_t q);
int						cfb_e(t_parse *p, int64_t q);
int						cfb_d(t_parse *p, int64_t q);
int						ecb3_e(t_parse *p, int64_t q);
int						ecb3_d(t_parse *p, int64_t q);
int						cbc3_e(t_parse *p, int64_t q);
int						cbc3_d(t_parse *p, int64_t q);
int						ofb3_e_d(t_parse *p, int64_t q);
int						cfb3_e(t_parse *p, int64_t q);
int						cfb3_d(t_parse *p, int64_t q);
int						des(t_parse *p);

#endif
