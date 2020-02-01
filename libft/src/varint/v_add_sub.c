/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_add_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:57:53 by ravard            #+#    #+#             */
/*   Updated: 2020/01/25 02:23:05 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int8_t				add_carry(V_TYPE a, V_TYPE b, int8_t c)
{
	int8_t			d;

	d = ((a & 1) + (b & 1) + (c & 1)) >> 1 & 1;
	return ((d + (a >> 1) + (b >> 1)) >> (V_BIT_LEN - 1));
}

/*
** a >= 0 et b >= 0
*/

static t_varint		v_add_pos(t_varint a, t_varint b)
{
	t_varint		ret;
	V_LEN_TYPE		len;
	int8_t			carr;
	V_LEN_TYPE		i;

	ret = g_v[0];
	len = (a.len >= b.len) ? a.len : b.len;
	carr = 0;
	i = -1;
	while (++i < len)
	{
		ret.x[i] = a.x[i] + b.x[i] + carr;
		carr = add_carry(a.x[i], b.x[i], carr);
	}
	if (carr)
	{
		ret.len = i + 1;
		ret.x[i] = carr;
	}
	else
		ret.len = i;
	return (ret);
}

/*
** a >= b >= 0
*/

static t_varint		v_sub_pos(t_varint a, t_varint b)
{
	t_varint		ret;
	V_LEN_TYPE		len;
	V_LEN_TYPE		i;
	uint8_t			c;

	ret = g_v[0];
	len = a.len;
	c = 0;
	i = -1;
	while (++i < len)
	{
		ret.x[i] = a.x[i] - (b.x[i] + c);
		c = (a.x[i] >= b.x[i] + c) ? 0 : 1;
	}
	v_len(&ret);
	return (ret);
}

t_varint			v_add(t_varint a, t_varint b, bool check)
{
	t_varint		ret;
	bool			tmp;
	t_varint		abs[2];

	if (check && !v_check(&a, &b, NULL, "add"))
		return (g_v[3]);
	abs[0] = v_abs(a);
	abs[1] = v_abs(b);
	if (a.sign == b.sign)
	{
		ret = v_add_pos(abs[0], abs[1]);
		ret.sign = a.sign;
	}
	else
	{
		tmp = v_cmp(abs, "-ge", abs + 1, false);
		ret = tmp ? v_sub_pos(abs[0], abs[1])
			: v_sub_pos(abs[1], abs[0]);
		ret.sign = tmp ? a.sign : b.sign;
	}
	return (ret);
}

t_varint			v_sub(t_varint a, t_varint b, bool check)
{
	b.sign *= -1;
	return (v_add(a, b, check));
}
