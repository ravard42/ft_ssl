#ifndef VARINT_H
# define VARINT_H

# include "libft.h"

/*
** VARIOUS SIZE INT STRUCT
*/

# define	V_ERR						"ERROR: g_v_r has been called\n"
# define V_BAD_LEN 				"ERROR: v.len <= 0 or v.len > MAX_LEN\ncheck for overflow\n"
# define V_NEG_POW 				"ERROR: neg pow not handle\n"
# define V_BAD_SUB 				"ERROR: a < b in v_pos_sub\n"
# define	V_ADD_OVFL				"ERROR: operand size too big in v_add or v_sub, increase V_MAX_LEN\n"
# define	V_MUL_OVFL				"ERROR: operand size too big in v_mul, increase V_MAX_LEN\n"
# define	V_DIV_MOD_OVFL			"ERROR: operand size too big in v_div or v_mod, increase V_MAX_LEN\n"
# define	V_EXP_OVFL				"ERROR: operand size too big in v_exp, increase V_MAX_LEN\n"
# define	V_EXP_LIM				"ERROR: in v_exp, expo lim value overtaken\n"
# define	V_EXPMOD_OVFL			"ERROR: operand size too big in v_expmod, increase V_MAX_LEN\n"
# define V_DIV_BY_0 				"ERROR: division by 0\n"
# define V_INV_MOD_ERR 			"ERROR: elem not inversible for this modulo\n"
# define V_DER_INT_SEQ_ONLY	"ERROR: asn1 der alg only handle sequence of integers\n"
# define V_DER_2_BIG				"ERROR: to big file in asn1 der (header len must be <= 0xffff)\n"
# define V_DER_COR				"ERROR: der file corrupted\n"

//# define V_TYPE 			uint64_t
//# define	V_MID_INF		0xffffffff
//# define	V_SUP				0xffffffffffffffff
# define V_TYPE 			uint8_t
# define	V_MID_INF		0xf
# define	V_SUP				0xff
# define V_LEN				(int8_t)sizeof(V_TYPE)
# define V_BIT_LEN		((int8_t)sizeof(V_TYPE) * 8)

/*
**	overflow protection note: 	
**			1] when computing operations on varint numbers, particularly multiplications,
**				we need at most to twice the size of the operands
**				we then add one more data block for the algorithm needs.
**			2] V_LEN_TYPE must not overflow with V_MAX_LEN (beware that V_LEN_TYPE is signed) 
*/

# define V_DEMI_LEN		32
# define V_MAX_LEN		V_DEMI_LEN * 2 + 1
//# define V_MAX_LEN		65
# define V_LEN_TYPE		int16_t

typedef struct				s_varint
{
	int8_t					sign;
	V_TYPE					x[V_MAX_LEN];
	V_LEN_TYPE				len;
}
								t_varint;

/*
**	DER decoding linkedList
**
** id: integer id (first 0 and -1 for sequence conteneur)
**	st_h: starting der_header ptr
**	st_h: starting der_value  ptr
** len:	len of the der_value in byte
*/
typedef struct s_der_d t_der_d;
typedef struct			s_der_d
{
	int					id;
	uint8_t				*st_h;
	uint8_t				*st;
	int					len;
	t_der_d				*nxt;	
}							t_der_d;

typedef struct s_read t_read;

/*
**		g_v array regroups often used varint values
**
**		index		value
**		  0		  0
**		  1		  1
**		  2		  2
**		  3		 err
*/

static const t_varint	g_v[4] = {{1, {0}, 1},
											{1, {1}, 1},
											{1, {2}, 1},
											{0, {0}, 1}};

bool							is_g_v(int8_t i, t_varint v);
int8_t						v_check(t_varint a, t_varint b, t_varint m, char *op);
int64_t						v_maxbin_pow(t_varint v);
t_varint						v_init(char sign, V_TYPE *src, V_LEN_TYPE len);
void							v_len(t_varint *v);
t_varint    				v_abs(t_varint v);
void							v_print(t_varint *v, char *name, int64_t number, char *col);

void        				v_sort(t_varint *a, t_varint *b);
bool							v_cmp(t_varint a, char *cmp, t_varint b);
int8_t						add_carry(V_TYPE a, V_TYPE b, int8_t c);
t_varint						v_add(t_varint a, t_varint b);
t_varint						v_sub(t_varint a, t_varint b);
t_varint 					v_inc(t_varint a);
t_varint 					v_dec(t_varint a);
t_varint						v_mul(t_varint a, t_varint b);
t_varint						v_exp(t_varint v, t_varint e);
t_varint						v_div(t_varint dend, t_varint sor);
t_varint						v_mod(t_varint dend, t_varint sor, bool pos);
t_varint    				v_expmod(t_varint v, t_varint e, t_varint mod, bool pos);
t_varint						v_rand_n(int fd, V_LEN_TYPE len);
t_varint						v_gcd(t_varint a, t_varint b);
void							v_eea(t_varint *coef_r0, t_varint a, t_varint b);
t_varint						v_inv(t_varint v, t_varint mod);
t_varint						v_crt(t_varint v, t_varint e, t_varint p, t_varint q);
int							v_asn1_der_int_seq_e(char *out, t_varint *v, int nb_varint);
t_varint						*v_asn1_der_int_seq_d(int *nb_varint, t_read *r);

#endif
