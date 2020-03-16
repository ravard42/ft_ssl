/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csprng.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 07:01:13 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 03:59:36 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool		seeding(t_rng *rng)
{
	uint64_t		buff[3];
	
	if (rng->co >= 0xa00000)
	{
		rng->co = 0;
		if (read(rng->fd, &buff, 24) != 24
			&& ft_dprintf(2, "%s%s%s\n", KRED, SEED_ERR, KNRM))
			return (false);
		ft_memcpy(rng->s.arg[0].x, buff, 24);
		format_key(&rng->s, 3);
		return (true);
	}
	return (true);
}

/*
** load len pseudo random bytes from des3 csprng in dest
** beware that dest have enough space memory for len bytes
**
** NB : csprng seeding process on rng->fd
**		by default points on /dev/urandom
** 	treshold set at 0xa00000 for reseeding (~10min)
*/

void			*prng(void *dest, size_t len, t_rng *rng)
{
	uint64_t	buff;
	int			i;
	int			q;
	int			r;

	if (!seeding(rng))
		return (NULL);
	q = len / 8;
	i = -1;
	while (++i < q)
	{
		buff = des3_block_e(++rng->co, &rng->s);
		ft_memcpy(dest + i * 8, &buff, 8);
	}
	if ((r = len % 8))
	{
		buff = des3_block_e(++rng->co, &rng->s);
		ft_memcpy(dest + i * 8, &buff, r);
	}
	*((uint8_t *)dest + len - 1) += (*((uint8_t *)dest + len - 1))
		? 0x00 : 0x01;
	return (dest);
}
