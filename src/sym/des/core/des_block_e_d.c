/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_e_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:12:15 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:04:29 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t			des_block_e(uint64_t x, t_sym *s)
{
	int8_t	i;

	x = (s->endian) ? x : bswap64(x);
	x = initial_perm(x);
	s->l = (uint32_t)(x >> 32);
	s->r = (uint32_t)(x & 0xffffffff);
	i = -1;
	while (++i < 16)
		des_round(s, i);
	x = (uint64_t)s->l + ((uint64_t)s->r << 32);
	x = final_perm(x);
	x = (s->endian) ? x : bswap64(x);
	return (x);
}

uint64_t			des_block_d(uint64_t x, t_sym *s)
{
	int8_t	i;

	x = (s->endian) ? x : bswap64(x);
	x = initial_perm(x);
	s->l = (uint32_t)(x >> 32);
	s->r = (uint32_t)(x & 0xffffffff);
	i = 16;
	while (--i >= 0)
		des_round(s, i);
	x = (uint64_t)s->l + ((uint64_t)s->r << 32);
	x = final_perm(x);
	x = (s->endian) ? x : bswap64(x);
	return (x);
}

uint64_t			des3_block_e(uint64_t x, t_sym *s)
{
	s->id_k = 0;
	x = des_block_e(x, s);
	s->id_k = 1;
	x = des_block_d(x, s);
	s->id_k = 2;
	x = des_block_e(x, s);
	return (x);
}

uint64_t			des3_block_d(uint64_t x, t_sym *s)
{
	s->id_k = 2;
	x = des_block_d(x, s);
	s->id_k = 1;
	x = des_block_e(x, s);
	s->id_k = 0;
	x = des_block_d(x, s);
	return (x);
}
