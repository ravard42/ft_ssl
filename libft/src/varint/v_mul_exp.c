/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_mul_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:59:40 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 06:44:51 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**		     a|b   c|d
**            x  *  y
**
**	|sup = a * c||inf = b * d|
**	     |mid[0] = a * d|
**	     |mid[1] = b * c|
**
**	|----upper------lower----|
*/

static V_TYPE		upper(V_TYPE x, V_TYPE y)
{
	V_TYPE			abcd[4];
	V_TYPE			sup;
	V_TYPE			mid[2];
	V_TYPE			inf;
	V_TYPE			to_upper[2];

	abcd[0] = x >> V_BIT_LEN / 2;
	abcd[1] = x & V_MID_INF;
	abcd[2] = y >> V_BIT_LEN / 2;
	abcd[3] = y & V_MID_INF;
	sup = abcd[0] * abcd[2];
	mid[0] = abcd[0] * abcd[3];
	mid[1] = abcd[1] * abcd[2];
	inf = abcd[1] * abcd[3];
	to_upper[0] = (mid[0] >> V_BIT_LEN / 2)
		+ (mid[1] >> V_BIT_LEN / 2);
	to_upper[1] = ((mid[0] & V_MID_INF) + (mid[1] & V_MID_INF)
			+ (inf >> V_BIT_LEN / 2)) >> V_BIT_LEN / 2;
	return (sup + to_upper[0] + to_upper[1]);
}

/*
** i : a index
** j : b index <-> p_mul id <-> coincide with initial number of right 0 in p_mul
*/

static void			partial_mul(t_varint *p_mul, t_varint a, V_TYPE bxj)
{
	V_LEN_TYPE		i;
	V_TYPE			tmp;
	V_TYPE			upp;
	int8_t			carr;

	carr = 0;
	upp = 0;
	i = -1;
	while (++i < a.len)
	{
		tmp = a.x[i] * bxj;
		p_mul->x[p_mul->len] = tmp + upp + carr;
		p_mul->len++;
		carr = add_carry(tmp, upp, carr);
		upp = upper(a.x[i], bxj);
	}
	if ((tmp = upp + carr) > 0)
	{
		p_mul->x[p_mul->len] = tmp;
		p_mul->len += 1;
	}
	v_len(p_mul);
}

t_varint			v_mul(t_varint a, t_varint b, bool check)
{
	t_varint		ret;
	t_varint		p_mul;
	V_LEN_TYPE		j;
	int8_t			sign;

	if (check && !v_check(&a, &b, NULL, "mul"))
		return (g_v[3]);
	sign = a.sign * b.sign;
	a.sign = 1;
	b.sign = 1;
	ret = g_v[0];
	j = -1;
	while (++j < b.len)
	{
		p_mul = g_v[0];
		p_mul.len = j;
		partial_mul(&p_mul, a, b.x[j]);
		ret = v_add(ret, p_mul, false);
		if (is_g_v(3, &ret))
			return (ret);
	}
	ret.sign = sign;
	return (ret);
}

/*
** i : varint index
** j : bit index
*/

t_varint			v_exp(t_varint v, t_varint e)
{
	V_LEN_TYPE					i;
	int8_t						j;
	t_varint					ret;

	if (!v_check(&v, &e, NULL, "exp"))
		return (g_v[3]);
	if (is_g_v(0, &e))
		return (g_v[1]);
	j = V_BIT_LEN - 1;
	while (!(e.x[e.len - 1] >> j & 1))
		j--;
	ret = v;
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			ret = v_mul(ret, ret, false);
			if (e.x[i] >> j & 1)
				ret = v_mul(ret, v, false);
		}
	}
	return (ret);
}
