/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:13:35 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:03:06 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t		initial_perm(uint64_t x)
{
	uint64_t		y;
	int8_t			i;
	uint64_t		mask;

	y = 0;
	i = -1;
	while (++i < 64)
	{
		mask = (uint64_t)1 << (63 - i);
		y |= (g_ip[i] >= i) ? (x << (g_ip[i] - i)) & mask
				: (x >> (i - g_ip[i])) & mask;
	}
	return (y);
}

uint64_t		final_perm(uint64_t x)
{
	uint64_t		y;
	int8_t			i;
	uint64_t		mask;

	y = 0;
	i = -1;
	while (++i < 64)
	{
		mask = (uint64_t)1 << (63 - i);
		y |= (g_fp[i] >= i) ? (x << (g_fp[i] - i)) & mask
				: (x >> (i - g_fp[i])) & mask;
	}
	return (y);
}

uint32_t		round_perm(uint32_t x)
{
	uint32_t		y;
	int8_t			i;
	uint32_t		mask;

	y = 0;
	i = -1;
	while (++i < 32)
	{
		mask = (uint32_t)1 << (31 - i);
		y |= (g_p[i] >= i) ? (x << (g_p[i] - i)) & mask
				: (x >> (i - g_p[i])) & mask;
	}
	return (y);
}

uint64_t		expansion_perm(t_sym *s)
{
	uint64_t		y;
	uint64_t		tmp;
	int8_t			i;
	uint64_t		mask;

	y = 0;
	tmp = (s->endian) ? (uint64_t)s->r << 32 : (uint64_t)s->r << 32;
	i = -1;
	while (++i < 48)
	{
		mask = (uint64_t)1 << (63 - i);
		if (i <= 31)
			y |= (g_e[i] >= i) ? (tmp << (g_e[i] - i)) & mask
				: (tmp >> (i - g_e[i])) & mask;
		else
			y |= tmp >> (i - g_e[i]) & mask;
	}
	return (y);
}
