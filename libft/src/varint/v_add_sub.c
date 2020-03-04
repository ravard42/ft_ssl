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

/*
** binary decomposition
** a = 1 * 2^n +  a_n-1 * 2^(n - 1) + ... + 2^0 * a_0
** b = 1 * 2^m +  b_m-1 * 2^(m - 1) + ... + 2^0 * b_0
**
** msb_id(a) = (a != 0) ? n : -1
** msb_id(b) = (b != 0) ? m : -1
*/

/*
** V_ADD|V_SUB OVFL NOTE
**
** a.sign == b.sign
** msb_id(a + b) <= sup(n, m) + 1
**
** a.sign != b.sign
** msb_id(a + b) <= sup(n, m)
*/

bool			v_add_check(t_varint *v[3])
{
	int16_t	msb[3];

	msb[0] = v_msb_id(v[0]);
	msb[1] = v_msb_id(v[1]);
	msb[2] = (msb[0] >= msb[1]) ? msb[0] : msb[1];
	msb[2] += v[0]->sign == v[1]->sign ? 1 : 0;
	if (1 + msb[2] / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (false);
	return (true);
}

t_varint		v_add_pos(t_varint a, t_varint b)
{
	uint64_t		*u64[2];
	int16_t		len;
	int16_t		i;
	uint64_t		tmp;
	uint8_t		carry;
	
	u64[0] = (uint64_t *)a.x;
	u64[1] = (uint64_t *)b.x;
	len = a.len / (ssize_t)sizeof(uint64_t);
	len += (a.len % (ssize_t)sizeof(uint64_t)) ? 1 : 0;
	carry = 0;
	i = -1;
	while (++i < len)
	{
		tmp = *u64[0];
		*u64[0] += *u64[1] + carry;
		carry = (tmp > *u64[0]) ? 1 : 0;
		u64[0]++;
		u64[1]++;
	}
	*u64[0] += carry;
	v_len(&a, 8 * len + carry);
	return (a);
}

/*
** a >= b >= 0 (cf v_sort in v_add)
*/

t_varint				v_sub_pos(t_varint a, t_varint b)
{
	uint64_t		*u64[2];
	int16_t		len;
	int16_t		i;
	uint8_t		carry[2];

	u64[0] = (uint64_t *)a.x;
	u64[1] = (uint64_t *)b.x;
	len = a.len / (ssize_t)sizeof(uint64_t);
	len += (a.len % (ssize_t)sizeof(uint64_t)) ? 1 : 0;
	carry[0] = 0;
	i = -1;
	while (++i < len)
	{
		carry[1] = (*u64[0] >= *u64[1] + carry[0]) ? 0 : 1;
		*u64[0] -= *u64[1] + carry[0];
		carry[0] = carry[1];
		u64[0]++;
		u64[1]++;
	}
	v_len(&a, len * 8);
	return (a);
}

/*
** note that v_sort here is in absolute mode (cf v_tools.c)
*/

t_varint			v_add(t_varint a, t_varint b, bool check)
{
	int8_t		sign[2];

	if (check && !v_check(&a, &b, NULL, "add"))
		return (g_v[3]);
	v_sort(&a, &b, sign);
	if (sign[0] == sign[1])
		a = v_add_pos(a, b);
	else
		a = v_sub_pos(a, b);
	a.sign = sign[0];
	return (a);
}

t_varint			v_sub(t_varint a, t_varint b, bool check)
{
	int8_t		sign[2];

	b.sign *= -1;
	if (check && !v_check(&a, &b, NULL, "add"))
		return (g_v[3]);
	v_sort(&a, &b, sign);
	if (sign[0] == sign[1])
		a = v_add_pos(a, b);
	else
		a = v_sub_pos(a, b);
	a.sign = sign[0];
	return (a);
}
