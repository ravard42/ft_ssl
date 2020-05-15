/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:07:08 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:41:21 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			fi(uint32_t *h, uint32_t *tmp, int64_t i)
{
	if (i >= 0 && i < 16)
	{
		tmp[0] = i;
		tmp[1] = f0(h);
	}
	else if (i >= 16 && i < 32)
	{
		tmp[0] = (5 * i + 1) % 16;
		tmp[1] = f1(h);
	}
	else if (i >= 32 && i < 48)
	{
		tmp[0] = (3 * i + 5) % 16;
		tmp[1] = f2(h);
	}
	else if (i >= 48 && i < 64)
	{
		tmp[0] = (7 * i) % 16;
		tmp[1] = f3(h);
	}
}

void				md5_block_hash(t_hash *hash, char *pad, int64_t *id_block)
{
	uint32_t		w[16];
	uint32_t		h[4];
	uint32_t		tmp[3];
	int64_t			i;

	ft_memcpy(w, pad + *id_block * 64, 64);
	ft_memcpy(h, hash->h, 16);
	i = -1;
	while (++i < 64)
	{
		fi(h, tmp, i);
		tmp[2] = h[3];
		h[3] = h[2];
		h[2] = h[1];
		h[1] = rot_l(h[0] + tmp[1] + hash->k[i] + w[tmp[0]], hash->s[i]) + h[1];
		h[0] = tmp[2];
	}
	i = -1;
	while (++i < 4)
		hash->h[i] += h[i];
	(*id_block)++;
}
