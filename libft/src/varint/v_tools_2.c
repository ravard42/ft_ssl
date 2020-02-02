/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_tools_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:38:00 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 02:44:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int64_t					v_maxbin_pow(t_varint *v)
{
	int64_t	j;

	if (is_g_v(0, v))
		return (-1);
	j = V_BIT_LEN - 1;
	while (j != -1 && !(v->x[v->len - 1] >> j & 1))
		j--;
	if (j == -1
		&& ft_dprintf(2, "%s%s%s\n", KRED, V_COR_LEN, KNRM))
		return (-1);
	j += (v->len - 1) * V_BIT_LEN;
	return (j);
}

t_varint				*v_inc(t_varint *a)
{
	*a = v_add(*a, g_v[1], true);
	return (a);
}

t_varint				*v_dec(t_varint *a)
{
	*a = v_sub(*a, g_v[1], true);
	return (a);
}

t_varint				v_abs(t_varint v)
{
	v.sign = 1;
	return (v);
}

/*
** load len pseudo random V_TYPE from /dev/urandom in a varint variable and return it
*/

t_varint				v_rand(V_LEN_TYPE len, bool neg)
{
	V_TYPE			rand_n[len];
	t_varint		n;
	uint8_t			sign;

	if (neg)
	{
		ft_rand(&sign, 1);
		sign = (sign % 2) ? 1 : -1;
	}
	else
		sign = 1;
	ft_rand(rand_n, len * V_LEN);
	n = v_init(sign, rand_n, len);
	return (n);
}
