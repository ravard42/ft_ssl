/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_div_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:02:11 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 03:25:12 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void				v_feed(t_varint *dst, t_varint *src, int64_t *cursor)
{
	uint64_t	q;
	uint64_t	r;

	q = *cursor / V_BIT_LEN;
	r = *cursor % V_BIT_LEN;
	*dst = v_mul(*dst, g_v[2], false);
	dst->x[0] |= ((uint64_t)src->x[q] >> r) & 1;
	src->x[q] &= ~((uint64_t)1 << r);
	(*cursor)--;
}

static t_varint			v_shift_substract(t_varint dend, char *op, t_varint sor)
{
	int64_t			cursor;
	t_varint		q;
	t_varint		r;

	if ((cursor = v_maxbin_pow(&dend)) == -1)
		return (g_v[0]);
	q = g_v[0];
	r = g_v[0];
	while (cursor != -1)
	{
		v_feed(&r, &dend, &cursor);
		if (v_cmp(&r, "-lt", &sor, false))
			q = v_mul(q, g_v[2], false);
		else
		{
			r = v_sub(r, sor, false);
			q = v_mul(q, g_v[2], false);
			q.x[0] |= 1;
		}
		if (cursor == -1 && !ft_strcmp(op, "mod"))
			return (r);
	}
	return (q);
}

t_varint				v_div(t_varint dend, t_varint sor, bool check)
{
	t_varint		q;
	int8_t			sign;

	if (check && !v_check(&dend, &sor, &g_v[0], "div"))
		return (g_v[3]);
	sign = dend.sign * sor.sign;
	dend.sign = 1;
	sor.sign = 1;
	q = v_shift_substract(dend, "div", sor);
	q.sign = sign;
	return (q);
}

/*
** 	1]
**	pos == false -> behave like % operator
**		ex: -12 % 5 will return -2
**	2]
**	pos == true	 -> behave like true euclidian divison reminder
**		ex: -12 mod 5 will return 3
*/

t_varint				v_mod(t_varint dend, t_varint sor, bool eucl,
		bool check)
{
	t_varint		r;
	int8_t			sign;

	if (check && !v_check(&dend, &sor, &g_v[0], "div"))
		return (g_v[3]);
	sign = dend.sign;
	dend.sign = 1;
	sor.sign = 1;
	r = v_shift_substract(dend, "mod", sor);
	r.sign = (eucl) ? 1 : sign;
	if (eucl && sign == -1)
		r = v_sub(sor, r, false);
	return (r);
}
