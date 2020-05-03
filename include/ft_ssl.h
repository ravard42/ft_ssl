/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:58:03 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 04:04:13 by ravard           ###   ########.fr       */
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
# include "first_primes.h"

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31;1m"
# define KGRN  "\x1B[32;1m"
# define KYEL  "\x1B[33;1m"
# define KBLU  "\x1B[34;1m"
# define KMAG  "\x1B[35;1m"
# define KCYN  "\x1B[36;1m"
# define KWHT  "\x1B[37;1m"

/*
** USAGE MSGS
*/
# define U "%susage%s: ./ft_ssl %scommand %s[opts]%s [args]\n"
# define P "-p, echo STDIN to STDOUT and append the checksum to STDOUT"
# define Q "-q, quiet mode, only print the checksum"
# define R "-r, reverse the format of the output"
# define S "-s, print the sum of the given string"
# define E "-e, encode/encrypt mode (default)"
# define D "-d, decode/decrypt mode"
# define I "-i, input file"
# define O "-o, output file"
# define DES "\x1B[33;1mdes:\x1B[0m"
# define A " -a, decode/encode the input/output in base64"
# define K " -k, key in hexa is the next argument."
# define V " -v, initialization vector in hexa is the next argument."
# define SALT " -s, the salt in hexa is the next argument."
# define PW " -p, password in ascii is the next argument."
# define RAND "-rand file, use file data to seed the random number generator"
# define IN "-in file (default stdin)"
# define OUT "-out file (default stdout)"
# define NB "numbits, size of the modulus in bits express in decimal (must be the last option specified, default 128 bits)"
# define IF "-inform DER|PEM , key input format expected on -in (default PEM)"
# define OF "-outform DER|PEM , key output format expected on -out (default PEM)"
# define PI "-passin, des password for reading is the next arg (decrypt)"
# define PO "-passout, des password for writing is the next arg (encrypt)"
# define ENC "-des, encrypt private key with des before writing it\n  (pbkdf is used, if -passout not present, user will be prompted for a pass phrase)"
# define PBI "-pubin, private key is read by default on -in, with this option a public key is read instead"
# define PBI2 "-pubin, private key is read by default on -inkey, with this option a public key is read instead"
# define PBO "-pubout, private key is output by default on -out, with this option a public key is output instead"
# define T "-text, print key components and key encoded version"
# define M "-modulus, print out the value of the modulus of the key"
# define N "-noout, this option prevents output of the encoded version of the key"
# define C "-check, check the consistency of an RSA private key"
# define IK "-inkey val, input key"
# define RSA_E "-encrypt, encrypt with public key"
# define RSA_D "-decrypt, decrypt with private key"
# define HEXD	"-hexdump, hex dump the output data"
# define RAW	"-raw, no padding applied (default PKCS#1 v1.5)"


# define GENRSA_RUNNING "Generating RSA private key, %hd bit long modulus (2 primes)\n"

#define CHECK_SUCCESS	"%sRSA key ok%s\n"

/*
** ERROR MSGS 
** LOT OF WORK TO BE DONE HERE:
**	find your error msg style starting with varint.h error msgs
** and stay convenient here with it
*/



# define ERR_OUT_FD 		"%sout_file opening error%s\n"
# define ERR_GENRSA_LEN "%sV_MAX_LEN must be >= %d for this key size%s\n"
# define ERR_CHECK_LEN "%sV_MAX_LEN must be >= %d for checking this this key size%s\n"
#define R_CHECK_0 		"%sOnly private keys can be checked%s\n"
#define R_CHECK_1 		"%sRSA key error: p not prime%s\n"
#define R_CHECK_2 		"%sRSA key error: q not prime%s\n"
#define R_CHECK_3 		"%sRSA key error: d e not congruent to 1%s\n"
#define R_CHECK_4 		"%sRSA key error: dmp1 not congruent to d%s\n"
#define R_CHECK_5 		"%sRSA key error: dmq1 not congruent to d%s\n"
#define R_CHECK_6 		"%sRSA key error: iqmp not inverse of q%s\n"
#define	ERR_OPT_0		"%sNo key file specified%s\n"
#define	ERR_OPT_1		"%s-encrypt|-decrypt missing%s\n"
# define ERR_ENC_0 		"%sdata too small for key size%s\n"
# define ERR_ENC_1		"%sdata too large for key size%s\n"
# define ERR_ENC_2 		"%sdata too large for modulus%s\n"
# define ERR_DEC_0 		"%sonly private key can decrypt%s\n"
# define ERR_UNPAD_0 	"%sunpadding error 0%s\n"
# define ERR_UNPAD_1 	"%sunpadding error 1%s\n"

# define ERR_DATA_LEN 	"%sdata too large, V_MAX_LEN must be >= %d%s\n"

/*
** varint len <= 4096 (32768 bits) (cf varint.h)
** as we need to twice the memory space to compute operations on varint in rsa process it means we have an rsa key-size (modulus) treshold set to 16384 bits.
** In practice and because of rsa run-time limitation we set it to 4096 for modulus key-size.
** NB: rsautl need twice as many memory than genrsa and rsa cmds
*/

# define V_GENRSA_STACK_ERR "libft/include/varint.h bad stack setting\ngenrsa cmd need at least 8-byte varint for RSA-64\nand at most 512-byte for RSA-4096\n"
# define SEED_ERR "csprng seeding or reseeding failed: lack of random input data on rng->fd"

/*
**
*/

# define NB_MIL_RAB 2

# define SH_L(x, n) ((x) << (n))
# define ROT_L(x, n) (((x) << (n)) | ((x) >> (32-(n))))
# define SH_R(x, n) ((x) >> (n))
# define ROT_R(x, n) (((x) >> (n)) | ((x) << (32-(n))))

# define ROT_28_LEFT(x, n) (((x)<<(n)) | ((x)>>(28-(n)))) & 0xfffffff000000000


//# define EVP_BYTES_TO_KEY md5_pbkdf
# define EVP_BYTES_TO_KEY sha256_pbkdf

typedef struct		s_write
{
	int				fd;
	char			*msg;
	int64_t			len;
}					t_write;

/*
**	In hash commands:
**	t_write is used as a buffer for padding
**
**	In sym cipher commands:
**	t_write is the buffer where the t_read plaintext data
**	(respectively the t_read ciphertext data)
**	will be encrypted (respectively decrypted)
*/

typedef struct		s_hash
{
	uint8_t			o[5];
	uint32_t		s[64];
	uint32_t		k[64];
	uint32_t		h[8];
	bool			pbkdf;
}					t_hash;

/*
** HASH OPTIONS
**
** o[0] = 1 => traitement des opts désactivés
** o[1] : -p on/off
** o[2] : -q on/off
** o[3] : -r on/off
** o[4] : -s on/off
*/

typedef struct		s_arg
{
	uint64_t		x[3];
	char			*p;
	bool			set;
}					t_arg;

typedef struct		s_sym
{
	uint8_t			o[9];
	uint32_t		r;
	uint32_t		l;
	t_arg			arg[4];
	uint64_t		sub_k[48];
	uint8_t			id_k;
	uint8_t		endian;
}					t_sym;

/*
** SYM OPTIONS
** o[0] : -e on/off
** o[1] : -d on/off
** o[2] : -i on/off
** o[3] : -o on/off
** o[4] : -a on/off
** o[5] : -k on/off
** o[6] : -v on/off
** o[7] : -s on/off
** o[8] : -p on/off
**
** SYM ARGS
** arg[0] : k
** arg[1] : v
** arg[2] : s
** arg[3] : p
**
** endian = 1 if big endian 0 if little endian
*/

static const t_varint	g_f4 = {1, 3, {1, 0, 1}};


# define PEM_ENC_HEADER "Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC," 

typedef struct		s_asym
{
	uint8_t			o[13];
	int16_t			mod_nb;
	t_varint			*rsak;
	t_read			data;
}					t_asym;

/*	ASYM OPTIONS
**							GENRSA	RSA				RSAUTL
** o[0] :	 			-rand 	-in 				-in
** o[1] : 				-out		-out				-out
**	o[2] : 							-inform			-inkey
**									{PEM:0, DER:2}
**	o[3] : 							-outform			-pubin
**									{PEM:0, DER:2)
**	o[4] :							-passin			-encrypt
**	o[5] :							-passout			-decrypt
**	o[6] :							-des				-hexdump
**	o[7] :							-pubin			-raw
**	o[8] :							-pubout
**	o[9] :							-text
**	o[10] : 							-modulus
**	o[11] : 							-noout
**	o[12] : 							-check
**
**
**	OTHER ASYM ATT
** 	mod_nb 						: modulus number of bits
** 	rsa private key order 	: version, n, e, d, p, q, dp, dq, qinv
**		rsa public key order		: n, e
*/

typedef struct		s_rng
{
	int				fd;
	uint64_t		co;
	t_sym			s;
}					t_rng;

/*
** RNG ATTR
** fd : fd for seed triple des key
** co : csprng triple des counter (input)
**	s	: t_sym variable to compute 3des
*/

typedef struct		s_parse
{
	t_cmd			cmd;
	uint8_t			i[3];
	char			*in_file;
	t_read			r;
	char			*out_file;
	t_write			w;
	t_hash			h;
	t_sym			s;
	t_asym			a;
	t_rng			rng;
}					t_parse;

/*
** NOTE: state attribut t_parse <-> i
**
** i[0] indice de l'argument en cours de traitement
** i[1] == 1 <-> on a déjà lu sur stdin (hash only)
** i[1] == 2 <-> file to be decrypt salted (sym only)
** i[2] nombre de print sur stdout (hash only)
*/

/*
** PARSER
*/
bool					cmd_parser(t_parse *p, char *arg);
bool					opt_parser(t_parse *p, const char **opts, char *arg);
int					str_parser(t_parse *p, char *arg);
int					fd_parser(t_parse *p, char *arg);
int					cmd_usage(void);
int					opt_usage(char *title, const char **usg);
bool					init_p(t_parse *p, char *cmd, uint8_t init_opt);
void				free_p(t_parse *p, uint8_t free_opt);
/*
** HASH CRYPTOGRAPHY
*/
int					hash_parser(t_parse *p, int argc, char **argv);
char				*hash_padding(t_parse *p);
void				print_format(t_parse *p, t_hash *hash);
/*
** md5
*/
int					md5(t_parse *p);
void				md5_init(t_hash *hash);
uint32_t			f0(uint32_t *h);
uint32_t			f1(uint32_t *h);
uint32_t			f2(uint32_t *h);
uint32_t			f3(uint32_t *h);
void				md5_block_hash(t_hash *hash, char *pad,
							int64_t *id_block);
/*
** sha256
*/
int					sha256(t_parse *p);
void				sha256_init(t_hash *hash);
uint32_t			g0(uint32_t *h);
uint32_t			g1(uint32_t *h);
uint32_t			g2(uint32_t *h);
uint32_t			g3(uint32_t *h);
uint32_t			g4(uint32_t *h);
uint32_t			g5(uint32_t *h);
void				sha256_block_hash(t_hash *hash, char *pad,
		int64_t *id_block);
/*
** SYM CRYPTOGRAPHY
*/
int					sym_parser(t_parse *p, int argc, char **argv);
void				format_key(t_sym *s, uint8_t nb_k);
/*
** base64
*/
uint32_t			be_transpo(uint32_t x);
void				del_whitespaces(t_read *r);
uint32_t			b64_block_e(uint32_t in, uint8_t k, uint8_t b_endian);
uint32_t			b64_block_d(uint32_t in, uint8_t *k, uint8_t b_endian);
int					run_b64_e(t_parse *p);
int					run_b64_d(t_parse *p);
int					b64(t_parse *p);
/*
** des
*/
int					des(t_parse *p);
int					des_dec(t_parse *p);
int					des_enc(t_parse *p);
int					check_out(t_parse *p);
int					check_k_v(t_parse *p);
char				*des_padding(t_parse *p);
int64_t				des_unpadding(t_write *w);
int					opt_a_e(t_parse *p);
int					opt_a_d(t_parse *p);
/*
** des/core
*/
uint64_t			parity_bit_drop(uint64_t key);
uint64_t			compress_d_box(uint64_t x);
void				load_sub_k(t_sym *s, uint8_t id_k);
uint64_t			initial_perm(uint64_t x);
uint64_t			final_perm(uint64_t x);
uint64_t			expansion_perm(t_sym *s);
uint32_t			round_perm(uint32_t x);
uint32_t			s_boxes(uint64_t x);
void				des_round(t_sym *s, uint8_t i);
uint64_t			des_block_e(uint64_t x, t_sym *s);
uint64_t			des_block_d(uint64_t x, t_sym *s);
uint64_t            des3_block_e(uint64_t x, t_sym *s);
uint64_t            des3_block_d(uint64_t x, t_sym *s);

/*
** des/pbkdf
*/
int					md5_pbkdf(t_parse *tmp, t_parse *p);
int					sha256_pbkdf(t_parse *tmp, t_parse *p);
char              *set_pass(bool verify);
int					pbkdf(t_parse *p, bool verify, char *salt);
/*
** des/mode
*/
int					ecb_e(t_parse *p);
int					ecb_d(t_parse *p);
int					cbc_e(t_parse *p);
int					cbc_d(t_parse *p);
int					ofb_e_d(t_parse *p);
int					cfb_e(t_parse *p);
int					cfb_d(t_parse *p);
int					ecb3_e(t_parse *p);
int					ecb3_d(t_parse *p);
int					cbc3_e(t_parse *p);
int					cbc3_d(t_parse *p);
int					ofb3_e_d(t_parse *p);
int					cfb3_e(t_parse *p);
int					cfb3_d(t_parse *p);
/*
** ASYM
*/
int					genrsa_parser(t_parse *p, int argc, char **argv);
int					rsa_parser(t_parse *p, int argc, char **argv);
int					rsautl_parser(t_parse *p, int argc, char **argv);
int					genrsa(t_parse *p);
bool					sieve(t_varint *n);
bool					prob_prime_test(t_varint *n, t_rng *rng, bool progress_bar);
int					read_rsak(t_parse *p);
int					write_rsak(t_parse *p, int nb_v);
int					rsa(t_parse *p);
int					rsautl(t_parse *p);
t_varint				cra(t_varint *data, t_varint *rsak);

/*
** csprng.c
*/
void				*prng(void *dest, size_t len, t_rng *r, uint8_t opts);
#endif
