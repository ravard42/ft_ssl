/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:44:37 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:46:59 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		init_block_hash(uint32_t *w, char *pad, int64_t *id_block)
{
	int				i;
	uint32_t		tmp;

	ft_memcpy(w, pad + *id_block * 64, 64);
	i = 15;
	while (++i < 64)
	{
		tmp = g5(w + i - 2) + w[i - 7] + g4(w + i - 15) + w[i - 16];
		ft_memcpy(w + i, &tmp, 4);
	}
}

void			sha256_block_hash(t_hash *hash, char *pad, int64_t *id_block)
{
	uint32_t		w[64];
	uint32_t		h[8];
	uint32_t		tmp[2];
	int64_t			i;

	init_block_hash(w, pad, id_block);
	ft_memcpy(h, hash->h, 8 * 4);
	i = -1;
	while (++i < 64)
	{
		tmp[0] = h[7] + g3(h + 4) + g0(h + 4) + hash->k[i] + w[i];
		tmp[1] = g2(h) + g1(h);
		h[7] = h[6];
		h[6] = h[5];
		h[5] = h[4];
		h[4] = h[3] + tmp[0];
		h[3] = h[2];
		h[2] = h[1];
		h[1] = h[0];
		h[0] = tmp[0] + tmp[1];
	}
	i = -1;
	while (++i < 8)
		hash->h[i] = hash->h[i] + h[i];
	(*id_block)++;
}
