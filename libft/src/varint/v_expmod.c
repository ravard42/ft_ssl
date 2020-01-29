/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_expmod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:05:03 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 03:26:12 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sqr_mul_mod(t_varint *ret, t_varint *v, t_varint *mod, bool eucl)
{
	if (v == NULL)
	{
		*ret = v_mul(*ret, *ret, false);
		*ret = v_mod(*ret, *mod, eucl, false);
	}
	else
	{
		*ret = v_mul(*ret, *v, false);
		*ret = v_mod(*ret, *mod, eucl, false);
	}
}

t_varint	v_expmod(t_varint v, t_varint e, t_varint mod, bool eucl)
{
	V_LEN_TYPE			i;
	int8_t				j;
	t_varint			ret;

	if (!v_check(&v, &e, &mod, "expmod"))
		return (g_v[3]);
	if (is_g_v(0, &e) && !is_g_v(1, &mod))
		return (g_v[1]);
	j = V_BIT_LEN - 1;
	while (((V_TYPE)e.x[e.len - 1] >> j & 1) == 0 && j)
		j--;
	ret = v_mod(v, mod, true, false);
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			sqr_mul_mod(&ret, NULL, &mod, eucl);
			if (e.x[i] >> j & 1)
				sqr_mul_mod(&ret, &v, &mod, eucl);
		}
	}
	return (ret);
}
