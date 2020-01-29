/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:02 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 03:24:29 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	binary decomposition
** a = 1 * 2^n +  a_n-1 * 2^(n - 1) + ... + 2^0 * a_0
** b = 1 * 2^m +  b_m-1 * 2^(m - 1) + ... + 2^0 * b_0
**
** maxbin_pow(a) = (a != 0) ? n : -1
** maxbin_pow(b) = (b != 0) ? m : -1
*/

/*
** a.sign == b.sign
** maxbin_pow(a + b) <= sup(n, m) + 1
**
** a.sign != b.sign
** maxbin_pow(a + b) <= sup(n, m)
*/

static bool				v_add_check(t_varint *a, t_varint *b)
{
	int64_t	mb_pow[3];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	mb_pow[2] = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	mb_pow[2] += a->sign == b->sign ? 1 : 0;
	if (1 + mb_pow[2] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (false);
	return (true);
}

/*
** maxbin_pow(a * b) <= n + m
*/

static bool				v_mul_check(t_varint *a, t_varint *b)
{
	int64_t	mb_pow[3];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	mb_pow[2] = mb_pow[0] + mb_pow[1];
	if (1 + mb_pow[2] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_MUL_OVFL, KNRM))
		return (false);
	return (true);
}

/*
**	(2^a)^b = 2^(a * b)
**
**		v < 2^(maxbin_pow(v) + 1)
**	=>	v^e < 2^((maxbin_pow(v) + 1) * e)
**
**	NB:stack-overflow occured on mac-mini at V_MAX_LEN ~ 300000 (uint8_t)
**		300000*8 = 2100000 (~2^21 bits)
**
**	if e >= 2^16 an error is raised
** explanation:
**	if we set v = e = 2^16
**	(2^16)^(2^16) = 2^(16 * 2^16) = 2^(2^4 * 2^16) = 2^(2^20)
**	it's almost the mac-mini stack limit of 2^21 bits
*/

static bool				v_exp_check(t_varint *v, t_varint *e)
{
	int8_t		i;
	uint64_t	e64;
	int64_t		mb_pow[2];

	if (e->sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (e->len * sizeof(V_TYPE) > 8
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_LIM, KNRM))
		return (false);
	e64 = 0;
	i = -1;
	while (++i < e->len)
		e64 += (uint64_t)e->x[i] << V_BIT_LEN * i;
	if (e64 > 0xffff
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_LIM, KNRM))
		return (false);
	mb_pow[0] = v_maxbin_pow(v);
	mb_pow[1] = (mb_pow[0] + 1) * e64;
	if (1 + mb_pow[1] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_OVFL, KNRM))
		return (false);
	return (true);
}

/*
**	can't overflow in div or mod
**	endeed quotient and modulus are always <= dividend
*/

static bool				v_div_check(t_varint *dividend, t_varint *divisor)
{
	int64_t	mb_pow;

	if (is_g_v(0, divisor)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	mb_pow = v_maxbin_pow(dividend);
	if (1 + mb_pow / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_OVFL, KNRM))
		return (false);
	return (true);
}

/*
** a^b mod(n) = (a mod(n))^b mod(n)
**
** expmod reduce a to a mod(n) from the entry of the function
**	so for overflow checking we only need to check that mod * mod don't overflow
*/

static bool				v_expmod_check(t_varint *v, t_varint *e, t_varint *mod)
{
	int64_t	mb_pow[2];

	(void)v;
	if (e->sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (false);
	if (is_g_v(0, mod)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (false);
	mb_pow[0] = v_maxbin_pow(mod);
	mb_pow[1] = mb_pow[0] * 2;
	if (1 + mb_pow[1] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXPMOD_OVFL, KNRM))
		return (false);
	return (true);
}

static bool				v_len_check(t_varint *v)
{
	V_LEN_TYPE		tmp;

	if ((v->len <= 0 || v->len > V_MAX_LEN)
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_LEN, KNRM))
		return (false);
	tmp = v->len;
	v_len(v);
	if (v->len != tmp && ft_dprintf(2, "%s%s%s\n", KRED, V_COR_LEN, KNRM))
		return (false);
	return (true);
}

/*
**	v_check verify that  a, b and m are valid varint variables:
**		1] sign == -1 or sign == 1
**		2] their len are consistent
**
**	morevover if op make sense:
**	v_check estimates if the resultat of op will not overflow V_MAX_LEN
**	and verify that the operation is well defined
**	(ex: divison by 0 same for a negative exponent)
*/

bool					v_check(t_varint *a, t_varint *b, t_varint *m, char *op)
{
	bool ret;

//	ft_printf("%sIN v_check_%s%s\n", KGRN, op, KNRM);
	if (is_g_v(3, a) || is_g_v(3, b) || is_g_v(3, m))
		ret = false;
	else if (!v_len_check(a) || !v_len_check(b) || !v_len_check(m))
		ret = false;
	else if (op && !ft_strcmp("add", op))
		ret = v_add_check(a, b);
	else if (op && !ft_strcmp("mul", op))
		ret = v_mul_check(a, b);
	else if (op && !ft_strcmp("exp", op))
		ret = v_exp_check(a, b);
	else if (op && !ft_strcmp("div", op))
		ret = v_div_check(a, b);
	else if (op && (!ft_strcmp("expmod", op)
				|| !ft_strcmp("crt", op)))
		ret = v_expmod_check(a, b, m);
	else
		ret = true;
//	ft_printf("%sOUT v_check_%s%s\n", KYEL, op, KNRM);
	return (ret);
}
