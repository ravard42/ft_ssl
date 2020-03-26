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

/*
** we recall that V_MAX_LEN <= 4096 bytes = 32768 bits
** v_msb_id can return a maximum of 32767  (int16_t)
** but it stay valid as it represents the index of the MSB (Most Significant Bit)
** and not the number of bits 
**
** v_msb_id need valid varint len!
**
** binary decomposition:
** a = 1 * 2^n +  a_n-1 * 2^(n - 1) + ... + 2^0 * a_0
** msb_id(a) = (a != 0) ? n : -1
*/

int16_t					v_msb_id(t_varint *v)
{
	int16_t	j;

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

t_varint				*v_inc(t_varint *a, bool check)
{
	*a = v_add(*a, g_v[1], check);
	return (a);
}

t_varint				*v_dec(t_varint *a, bool check)
{
	*a = v_sub(*a, g_v[1], check);
	return (a);
}

t_varint				v_abs(t_varint v)
{
	v.sign = 1;
	return (v);
}

/*
** load len pseudo random uint8_t chunk from /dev/urandom in a varint variable and return it
*/

t_varint				v_rand(int16_t len, bool neg)
{
	uint8_t			rand_n[len];
	t_varint		n;
	int8_t			sign;

	if (neg)
	{
		ft_rand(&sign, 1);
		sign = (sign % 2) ? 1 : -1;
	}
	else
		sign = 1;
	ft_rand(rand_n, len);
	n = v_init(sign, rand_n, len);
	return (n);
}
