/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_schedule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:10:46 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 16:40:12 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t				parity_bit_drop(uint64_t x)
{
	uint64_t		y;
	int8_t			i;
	uint64_t		mask;

	y = 0;
	i = -1;
	while (++i < 56)
	{
		mask = (uint64_t)1 << (63 - i);
		y |= (g_pc_1[i] >= i) ? (x << (g_pc_1[i] - i)) & mask
				: (x >> (i - g_pc_1[i])) & mask;
	}
	return (y);
}

uint64_t				compress_d_box(uint64_t x)
{
	uint64_t		y;
	int8_t			i;
	uint64_t		mask;

	y = 0;
	i = -1;
	while (++i < 48)
	{
		mask = (uint64_t)1 << (63 - i);
		y |= (g_pc_2[i] >= i) ? (x << (g_pc_2[i] - i)) & mask
				: (x >> (i - g_pc_2[i])) & mask;
	}
	return (y);
}

static uint64_t			rot_l_28(uint64_t x, uint8_t n)
{
	return ((((x) << (n)) | ((x) >> (28 - (n)))) & 0xfffffff000000000);
}

void					load_sub_k(t_sym *s, uint8_t id_k)
{
	uint64_t			tmp[2];
	uint8_t				i;

	tmp[0] = parity_bit_drop(*(s->arg[0].x + id_k)) & 0xFFFFFFF000000000;
	tmp[1] = parity_bit_drop(*(s->arg[0].x + id_k)) << 28;
	i = -1;
	while (++i < 16)
	{
		tmp[0] = (i <= 1 || i == 8 || i == 15) ?
				rot_l_28(tmp[0], 1) : rot_l_28(tmp[0], 2);
		tmp[1] = (i <= 1 || i == 8 || i == 15) ?
				rot_l_28(tmp[1], 1) : rot_l_28(tmp[1], 2);
		s->sub_k[i + id_k * 16] = compress_d_box(tmp[0] | (tmp[1] >> 28));
	}
}
