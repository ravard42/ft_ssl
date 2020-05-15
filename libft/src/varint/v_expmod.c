/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_expmod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:05:03 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:41:17 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** V_EXPMOD OVFL NOTE
**
** a^b mod(n) = (a mod(n))^b mod(n)
**
** expmod reduce 'a' to 'a mod(n)' from the entry of the function
** so for overflow checking we only need to check that n * n don't overflow
** (see V_MUL OVFL NOTE)
**
**
** a = v[0]
** b = v[1]
** n = v[2]
*/

bool			v_expmod_check(t_varint *v[3])
{
	int16_t	msb[2];
	int16_t	byte_len;

	if (v[1]->sign == -1
		&& ft_dprintf(2, g_v_sterr[V_ERR_NEG_POW], KRED, KNRM))
		return (false);
	if (is_g_v(0, v[2])
		&& ft_dprintf(2, g_v_sterr[V_ERR_DIV_0], KRED, KNRM))
		return (false);
	msb[0] = v_msb_id(v[2]);
	msb[1] = msb[0] * 2;
	byte_len = 1 + msb[1] / V_BIT_LEN;
	if (byte_len > V_MAX_LEN
		&& ft_dprintf(2, g_v_sterr[V_ERR_EXPMOD_OVFL], KRED, byte_len, KNRM))
		return (false);
	return (true);
}

static void		sqr_mul_mod(t_varint *ret, t_varint *v, t_varint *mod)
{
	if (v == NULL)
	{
		*ret = v_mul(*ret, *ret, false);
		*ret = v_mod(*ret, *mod, true, false);
	}
	else
	{
		*ret = v_mul(*ret, *v, false);
		*ret = v_mod(*ret, *mod, true, false);
	}
}

t_varint		v_expmod(t_varint v, t_varint e, t_varint mod, bool check)
{
	int16_t			i;
	int8_t			j;
	t_varint		ret;

	if (check && !v_check(&v, &e, &mod, "expmod"))
		return (g_v[3]);
	if (is_g_v(0, &e) && !is_g_v(1, &mod))
		return (g_v[1]);
	j = V_BIT_LEN - 1;
	while ((e.x[e.len - 1] >> j & 1) == 0 && j)
		j--;
	ret = v_mod(v, mod, true, false);
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			sqr_mul_mod(&ret, NULL, &mod);
			if (e.x[i] >> j & 1)
				sqr_mul_mod(&ret, &v, &mod);
		}
	}
	return (ret);
}
