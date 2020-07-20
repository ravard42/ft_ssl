/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varint.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 02:29:11 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 02:27:50 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARINT_H
# define VARINT_H

# include "libft.h"

/*
** VARIOUS SIZE INT STRUCT
*/

/*
** V_ERR_MSGS
*/

enum					e_v_errno {
	V_ERR,
	V_ERR_MAXLEN,
	V_ERR_LEN_0,
	V_ERR_LEN_1,
	V_ERR_DIV_0,
	V_ERR_NEG_POW,
	V_ERR_EXP_LIM,
	V_ERR_INV,
	V_ERR_DER_2BIG,
	V_ERR_DER_COR,
	V_ERR_DER_OVFL,
	V_ERR_LSHIFT_OVFL,
	V_ERR_ADD_OVFL,
	V_ERR_MUL_OVFL,
	V_ERR_EXP_OVFL,
	V_ERR_EXPMOD_OVFL,
	V_ERR_EEA_OVFL,
};

extern const char		*g_v_sterr[];

/*
**	V_MAX_LEN is the number maximum of 8-bit chunks
**	available for t_varint struct
*/

# define V_BIT_LEN			8
# define V_MAX_LEN		 	512

/*
** V_MAX_LEN must be a mutliple of 8 and <= 4096 (32768 bits)
*/

typedef struct				s_varint
{
	int8_t					sign;
	int16_t					len;
	uint8_t					x[V_MAX_LEN];
}							t_varint;

/*
**	overflow protection note:
**	1] when computing operations on varint numbers,
**		particularly multiplications,
**		we need at most to twice operand sup len
**		exemple: mul on 2 varint of len 16 needs 32 chunks
**	2] with V_MAX_LEN <= 4096
**		int16_t v.len can contain all possible byte len
**		and their associated Most Significant Bit ID (cf v_msb_id)
*/

typedef struct				s_der_d
{
	int						id;
	uint8_t					*st_h;
	uint8_t					*st;
	int						len;
	struct s_der_d			*nxt;
}							t_der_d;

/*
**	DER decoding linkedList
**
**  id: 	integer id (first 0 and -1 for sequence conteneur)
**	st_h: 	starting der_header ptr
**	st_h: 	starting der_value  ptr
** 	len:	len of the der_value in byte
*/

typedef struct s_read		t_read;
typedef bool				(*t_op_check)(t_varint *[3]);

static const t_varint		g_v[4] = {
	{1, 1, {0}},
	{1, 1, {1}},
	{1, 1, {2}},
	{0, 1, {0}}
};

/*
**		g_v array regroups often used one byte varint
**
**		index	value
**		  0		  0
**		  1		  1
**		  2		  2
**		  3		 err (sign != -1 && sign != 1)
*/

bool						is_g_v(int8_t i, t_varint *v);
void						v_len(t_varint *v, int16_t start_chunk);
t_varint					v_init(char sign, uint8_t *src, int16_t len);
void						v_print(int fd, char *name, t_varint *v,
		bool check);
int16_t						v_msb_id(t_varint *v);
t_varint					v_abs(t_varint v);
t_varint					*v_inc(t_varint *a, bool check);
t_varint					*v_dec(t_varint *a, bool check);
t_varint					v_rand(int16_t len, bool neg);

bool						v_check(t_varint *a, t_varint *b, t_varint *m,
		char *op);
bool						v_lshift_check(t_varint *v[3]);
bool						v_add_check(t_varint *v[3]);
bool						v_mul_check(t_varint *v[3]);
bool						v_exp_check(t_varint *v[3]);
bool						v_div_check(t_varint *v[3]);
bool						v_expmod_check(t_varint *v[3]);
bool						v_eea_check(t_varint *v[3]);

bool						v_cmp(t_varint *a, char *cmp, t_varint *b,
		bool check);
uint8_t						v_sort(t_varint *a, t_varint *b, int8_t *sign);
t_varint					v_left_shift(t_varint v, bool check);
t_varint					v_right_shift(t_varint v, bool check);
t_varint					v_add(t_varint a, t_varint b, bool check);
t_varint					v_sub(t_varint a, t_varint b, bool check);
t_varint					v_mul(t_varint a, t_varint b, bool check);
t_varint					v_exp(t_varint v, t_varint e);
t_varint					v_div(t_varint dend, t_varint sor, bool check);
t_varint					v_mod(t_varint dend, t_varint sor, bool eucl,
		bool check);
t_varint					v_expmod(t_varint v, t_varint e, t_varint mod,
		bool check);
t_varint					v_gcd(t_varint a, t_varint b, bool check);
t_varint					*v_eea(t_varint *coef_r0, t_varint a, t_varint b,
		bool check);
t_varint					v_inv(t_varint v, t_varint mod, bool check);

bool						v_asn1_int_seq_der_e(t_read *r, t_varint *v,
		int nb_varint);
int8_t						put_der_header(uint8_t *h, uint8_t type,
		unsigned int len);
t_varint					*v_asn1_int_seq_der_d(int *nb_varint, t_read *r);

#endif
