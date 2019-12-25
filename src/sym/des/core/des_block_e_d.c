/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_e_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:12:15 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 10:13:28 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t			des_block_e(uint64_t x, t_parse *p)
{
	int8_t	i;

	x = (p->cmd.endian) ? x : bswap64(x);
	x = initial_perm(x);
	p->s.l = (p->cmd.endian) ?
		*((uint32_t *)&x) : *((uint32_t *)&x + 1);
	p->s.r = (p->cmd.endian) ?
		*((uint32_t *)&x + 1) : *((uint32_t *)&x);
	i = -1;
	while (++i < 16)
		des_round(p, i);
	x = (uint64_t)p->s.l + ((uint64_t)p->s.r << 32);
	x = final_perm(x);
	x = (p->cmd.endian) ? x : bswap64(x);
	return (x);
}

uint64_t			des_block_d(uint64_t x, t_parse *p)
{
	int8_t	i;

	x = (p->cmd.endian) ? x : bswap64(x);
	x = initial_perm(x);
	p->s.l = (p->cmd.endian) ?
		*((uint32_t *)&x) : *((uint32_t *)&x + 1);
	p->s.r = (p->cmd.endian) ?
		*((uint32_t *)&x + 1) : *((uint32_t *)&x);
	i = 16;
	while (--i >= 0)
		des_round(p, i);
	x = (uint64_t)p->s.l + ((uint64_t)p->s.r << 32);
	x = final_perm(x);
	x = (p->cmd.endian) ? x : bswap64(x);
	return (x);
}

uint64_t			des_triple(uint64_t x, t_parse *p)
{
	bool	enc;

	enc = (!p->o[6] || !ft_strcmp("des-ede3-ofb", p->cmd.name)
			|| !ft_strcmp("des-ede3-cfb", p->cmd.name)) ? true : false;
	p->s.id_k = (enc) ? 0 : 2;
	x = (enc) ? des_block_e(x, p) : des_block_d(x, p);
	p->s.id_k = 1;
	x = (enc) ? des_block_d(x, p) : des_block_e(x, p);
	p->s.id_k = (enc) ? 2 : 0;
	x = (enc) ? des_block_e(x, p) : des_block_d(x, p);
	return (x);
}
