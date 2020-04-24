/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_div_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:02:11 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 01:19:08 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
** V_DIV|V_MOD OVFL NOTE
**
** v[0] -> dividend
** v[1] -> divisor
**
**	can't overflow in div or mod
**	endeed quotient and modulus are always <= dividend
*/

bool			v_div_check(t_varint *v[3])
{
	if (is_g_v(0, v[1])
		&& ft_dprintf(2, V_ERR_DIV_0, KRED, KNRM))
		return (false);
	return (true);
}

/*
** SHIFT and SUBSTRACT algorithm
**
** here dst is the remainder (r buffer in shift_substract scop)  
** that we feed with the upper bit of src (dividend) at every starting loop.
**	we then apply left_shift to quotient
** if r >= divisor
**		we substract divisor to r,
**		and turn the quotient LSB (Low Significant Bit) to one
**
** cursor represent where we are in the lecture of dividend
**
** optimization : before first loop, as left shifting 0 is doing nothing,
**						we feed r with first 64 chuncks of dividend
*/

static void				v_feed(t_varint *dst, t_varint *src, int16_t *cursor, int16_t *init_r)
{
	int16_t	q;
	int16_t	r;

	if (*init_r)
	{
		q = *init_r / V_BIT_LEN;
		ft_memcpy(dst->x, src->x + src->len - q, q);
		v_len(dst, q + 1);
		(*cursor) -= v_msb_id(dst) + 1;
		*init_r = 0;
	}
	else
	{
		q = *cursor / V_BIT_LEN;
		r = *cursor % V_BIT_LEN;
		*dst = v_left_shift(*dst, false);
		dst->x[0] |= (src->x[q] >> r) & 1;
		(*cursor)--;
	}
	
}

static t_varint			v_shift_substract(t_varint dend, char *op, t_varint sor)
{
	int16_t			cursor;
	t_varint		q;
	t_varint		r;
	int16_t		init_r;

	if ((cursor = v_msb_id(&dend)) == -1)
		return (g_v[0]);
	q = g_v[0];
	r = g_v[0];
	init_r = v_cmp(&dend, "-le", &sor, false) ? v_msb_id(&dend) : v_msb_id(&sor);
	while (cursor != -1)
	{
		v_feed(&r, &dend, &cursor, &init_r);
		q = v_left_shift(q, false);
		if (v_cmp(&r, "-ge", &sor, false))
		{
			r = v_sub(r, sor, false);
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

	if (check && !v_check(&dend, &sor, NULL, "div"))
		return (g_v[3]);
	sign = dend.sign * sor.sign;
	dend.sign = 1;
	sor.sign = 1;
	q = v_shift_substract(dend, "div", sor);
	q.sign = sign;
	return (q);
}

/*
** 1]
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

	if (check && !v_check(&dend, &sor, NULL, "div"))
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
