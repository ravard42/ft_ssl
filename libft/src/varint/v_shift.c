/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_shift.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 03:50:08 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:52:26 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** V_LEFT_SHIFT|V_RIGHT_SHIFT OVFL NOTE
**
** can't overflow in v_right_shift, and need one extra bit in v_left_shift
*/

bool			v_lshift_check(t_varint *v[3])
{
	int64_t	msb;
	int16_t	byte_len;

	msb = v_msb_id(v[0]) + 1;
	byte_len = 1 + msb / V_BIT_LEN;
	if (byte_len > V_MAX_LEN
		&& ft_dprintf(2, g_v_sterr[V_ERR_LSHIFT_OVFL], KRED, byte_len, KNRM))
		return (false);
	return (true);
}

static uint64_t	*init_shift(bool check, t_varint *v, int16_t *len, char *shift)
{
	if (check && !v_check(v, NULL, NULL, shift))
		return (NULL);
	*len = v->len / sizeof(uint64_t);
	*len += (v->len % sizeof(uint64_t)) ? 1 : 0;
	if (!ft_strcmp("left_shift", shift))
		return ((uint64_t*)v->x);
	return ((uint64_t*)v->x + *len);
}

t_varint		v_left_shift(t_varint v, bool check)
{
	int16_t		len;
	uint64_t	*u64;
	uint64_t	carry[2];
	int16_t		i;

	if (!(u64 = init_shift(check, &v, &len, "left_shift")))
		return (g_v[3]);
	carry[0] = 0;
	i = -1;
	while (++i < len)
	{
		carry[1] = (*u64 >> 63) & 1;
		*u64 <<= 1;
		*u64 |= carry[0];
		carry[0] = carry[1];
		u64++;
	}
	if (carry[0])
		*u64 |= carry[0];
	v_len(&v, len * 8 + carry[0]);
	return (v);
}

t_varint		v_right_shift(t_varint v, bool check)
{
	int16_t		len;
	uint64_t	*u64;
	uint64_t	carry[2];

	if (!(u64 = init_shift(check, &v, &len, "right_shift")))
		return (g_v[3]);
	carry[0] = 0;
	while (u64--)
	{
		carry[1] = *u64 & 1;
		*u64 >>= 1;
		*u64 |= carry[0] << 63;
		carry[0] = carry[1];
		if (u64 == (uint64_t *)v.x)
			break ;
	}
	v_len(&v, len * 8);
	return (v);
}
