/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 19:58:03 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 15:37:21 by ravard           ###   ########.fr       */
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
** WARNING: rsautl need twice as many memory than genrsa and rsa cmds
**
** for all t_varint variable v we have by def in libft/varint:
** v.len <= 4096 (32768 bits) (cf varint.h)
** as we need to twice the memory to compute operations in rsautl (expmod)
** it means we have an rsa key-size (modulus) treshold set to 16384 bits.
** In practice and because of rsa run-time limitation
** We set it to 4096 for modulus key-size.
*/

enum					e_ssl_strno {
	B64_ERR_0,
	B64_ERR_1,
	B64_ERR_2,
	DES_ERR_KVS,
	GRSA_ERR_LEN,
	GRSA_ERR_NB_0,
	GRSA_ERR_NB_1,
	GRSA_ERR_NB_2,
	GRSA_RUNNING,
	RSA_ERR_DES,
	RSA_ERR_CHECK_0,
	RSA_ERR_CHECK_1,
	RSA_ERR_CHECK_2,
	RSA_ERR_CHECK_3,
	RSA_ERR_CHECK_4,
	RSA_ERR_CHECK_5,
	RSA_ERR_CHECK_6,
	RSA_ERR_CHECK_7,
	RSA_CHECK_OK,
	RSA_TXT_PUB,
	RSA_TXT_PRV,
	RSAU_ERR_OPT_0,
	RSAU_ERR_OPT_1,
	RSAU_ERR_DATA_LEN_0,
	RSAU_ERR_DATA_LEN_1,
	RSAU_ERR_DATA_LEN_2,
	RSAU_ERR_DATA_LEN_3,
	RSAU_ERR_KEY,
	RSAU_ERR_UNPAD_0,
	RSAU_ERR_UNPAD_1,
	RSAU_ERR_OUT_FD,
	PRNG_ERR_OPEN_DEVURAND,
	PRNG_ERR_SEED,
	CRYPTA_ERR_LEN,
	CRYPTA_ERR_DATA
};

extern const char		*g_ssl_str[];
extern const char		*g_rsa_header[];

/*
** define EVP_BYTES_TO_KEY md5_pbkdf
*/
# define EVP_BYTES_TO_KEY sha256_pbkdf
# define NB_MIL_RAB 2

typedef struct			s_write
{
	int					fd;
	char				*msg;
	int64_t				len;
}						t_write;

/*
**	In hash commands:
**	t_write is used as a buffer for padding
**
**	In sym cipher commands:
**	t_write is the buffer where the t_read plaintext data
**	(respectively the t_read ciphertext data)
**	will be encrypted (respectively decrypted)
*/

typedef struct			s_hash
{
	uint8_t				o[5];
	uint32_t			s[64];
	uint32_t			k[64];
	uint32_t			h[8];
	bool				pbkdf;
}						t_hash;

/*
** HASH OPTIONS
**
** o[0] = 1 => traitement des opts désactivés
** o[1] : -p on/off
** o[2] : -q on/off
** o[3] : -r on/off
** o[4] : -s on/off
*/

typedef struct			s_arg
{
	uint64_t			x[3];
	char				*p;
	bool				set;
}						t_arg;

typedef struct			s_sym
{
	uint8_t				o[9];
	uint32_t			r;
	uint32_t			l;
	t_arg				arg[4];
	uint64_t			sub_k[48];
	uint8_t				id_k;
	uint8_t				endian;
}						t_sym;

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

typedef struct			s_asym
{
	uint8_t				o[13];
	int16_t				mod_nb;
	t_varint			*rsak;
	t_read				data;
}						t_asym;

/*
**	ASYM OPTIONS
**			GENRSA		RSA			RSAUTL
**	o[0] :	-rand 		-in 		-in
**	o[1] :	-out		-out		-out
**	o[2] : 				-inform		-inkey
**					{PEM:0, DER:2}
**	o[3] : 				-outform	-pubin
**					{PEM:0, DER:2)
**	o[4] :				-passin		-encrypt
**	o[5] :				-passout	-decrypt
**	o[6] :				-des		-hexdump
**	o[7] :				-pubin		-raw
**	o[8] :				-pubout
**	o[9] :				-text
**	o[10] : 			-modulus
**	o[11] : 			-noout
**	o[12] : 			-check
**
**	OTHER ASYM ATT
** 	mod_nb 						: modulus number of bits
** 	rsa private key order 		: version, n, e, d, p, q, dp, dq, qinv
**		rsa public key order	: n, e
*/

typedef struct			s_rng
{
	int					fd;
	uint64_t			co;
	t_sym				s;
}						t_rng;

/*
** RNG ATTR
** fd : fd for seed triple des key
** co : csprng triple des counter (input)
**	s	: t_sym variable to compute 3des
*/


typedef struct			s_crypta
{
	uint8_t				o[2];
	uint64_t				p;
	uint64_t				c;
}							t_crypta;

/*
**	CRYPTA OPTIONS
**
**	o[0] : plaintext 
**	o[1] : ciphertext
*/

typedef struct			s_parse
{
	t_cmd				cmd;
	uint8_t				i[3];
	char				*in_file;
	t_read				r;
	char				*out_file;
	t_write				w;
	t_hash				h;
	t_sym				s;
	t_asym				a;
	t_rng				rng;
	t_crypta			c;
}						t_parse;

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
int						str_parser(t_parse *p, char *arg);
int						fd_parser(t_parse *p, char *arg);
int						cmd_usage(void);
int						opt_usage(char *title, const char **usg);
bool					init_p(t_parse *p, char *cmd, uint8_t init_opt);
void					free_p(t_parse *p, uint8_t free_opt);
/*
** HASH CRYPTOGRAPHY
*/
int						hash_parser(t_parse *p, int argc, char **argv);
char					*hash_padding(t_parse *p);
void					print_format(t_parse *p, t_hash *hash);
uint32_t				sh_l(uint32_t x, uint8_t n);
uint32_t				sh_r(uint32_t x, uint8_t n);
uint32_t				rot_l(uint32_t x, uint8_t n);
uint32_t				rot_r(uint32_t x, uint8_t n);
/*
** md5
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
** sha256
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
** SYM CRYPTOGRAPHY
*/
int						sym_parser(t_parse *p, int argc, char **argv);
void					format_key(t_sym *s, uint8_t nb_k);
/*
** base64
*/
uint32_t				be_transpo(uint32_t x);
void					del_whitespaces(t_read *r);
uint32_t				b64_block_e(uint32_t in, uint8_t k, uint8_t b_endian);
uint32_t				b64_block_d(uint32_t in, uint8_t *k, uint8_t b_endian);
int						run_b64_e(t_parse *p);
int						run_b64_d(t_parse *p);
int						b64(t_parse *p);
/*
** des
*/
int						des(t_parse *p);
int						des_dec(t_parse *p);
int						des_enc(t_parse *p);
int						check_out(t_parse *p);
int						check_k_v(t_parse *p);
char					*des_padding(t_parse *p);
int64_t					des_unpadding(t_write *w);
int						opt_a_e(t_parse *p);
int						opt_a_d(t_parse *p);
/*
** des/core
*/
void					load_sub_k(t_sym *s, uint8_t id_k);
uint64_t				initial_perm(uint64_t x);
uint64_t				final_perm(uint64_t x);
uint64_t				expansion_perm(t_sym *s);
uint32_t				round_perm(uint32_t x);
uint32_t				s_boxes(uint64_t x);
void					des_round(t_sym *s, uint8_t i);
uint64_t				des_block_e(uint64_t x, t_sym *s);
uint64_t				des_block_d(uint64_t x, t_sym *s);
uint64_t				des3_block_e(uint64_t x, t_sym *s);
uint64_t				des3_block_d(uint64_t x, t_sym *s);

/*
** des/pbkdf
*/
int						md5_pbkdf(t_parse *tmp, t_parse *p);
int						sha256_pbkdf(t_parse *tmp, t_parse *p);
char					*set_pass(bool verify);
int						pbkdf(t_parse *p, bool verify, char *salt);
/*
** des/mode
*/
int						ecb_e(t_parse *p);
int						ecb_d(t_parse *p);
int						cbc_e(t_parse *p);
int						cbc_d(t_parse *p);
int						ofb_e_d(t_parse *p);
int						cfb_e(t_parse *p);
int						cfb_d(t_parse *p);
int						ecb3_e(t_parse *p);
int						ecb3_d(t_parse *p);
int						cbc3_e(t_parse *p);
int						cbc3_d(t_parse *p);
int						ofb3_e_d(t_parse *p);
int						cfb3_e(t_parse *p);
int						cfb3_d(t_parse *p);
/*
** ASYM
*/
int						genrsa_parser(t_parse *p, int argc, char **argv);
int						rsa_parser(t_parse *p, int argc, char **argv);
int						rsautl_parser(t_parse *p, int argc, char **argv);
int						genrsa(t_parse *p);
bool					sieve(t_varint *n);
bool					prob_prime_test(t_varint *n, t_rng *rng,
		bool progress_bar);

int						read_rsak(t_parse *p);
int						check_enc_header(int64_t *offset, t_parse *p);
int						pem_des_dec(t_parse *p);
int						write_rsak(t_parse *p, int nb_v);
int						des_enc_b64(t_parse *p, int nb_v);
int						rsa(t_parse *p);
int						rsautl(t_parse *p);
t_varint				cra(t_varint *data, t_varint *rsak);

/*
** csprng.c
*/
void					*prng(void *dest, size_t len, t_rng *r, uint8_t opts);
/*
** C-C-C_Combo_Breaker
*/

int			crypta_parser(t_parse *p, int argc, char **argv);
int			break_des_ecb(t_parse *p);


#endif
