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

static bool			seeding(t_rng *rng)
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
**
** option bits:
**	0x01	<->	not any 0x00 byte
**	0x02	<->	last byte is not 0x00
**
*/

static bool			any_zero(uint8_t *buff, int8_t len)
{
	int8_t		i;

	i = -1;
	while (++i < len)
		if (buff[i] == 0x00)
			return (true);
	return (false);
}

static void			des3_ctr(uint8_t *ptr, uint8_t size, t_rng *rng, uint8_t opts)
{
	uint64_t		buff;

	if (size == 0)
		return ;
	buff = des3_block_e(++rng->co, &rng->s);
	if (opts & 1)
		while (any_zero((uint8_t *)&buff, size))
			buff = des3_block_e(++rng->co, &rng->s);
	else if (opts & 2)
		while (any_zero((uint8_t *)&buff + size - 1, 1))
			buff = des3_block_e(++rng->co, &rng->s);
	ft_memcpy(ptr, &buff, size);
}

void					*prng(void *dest, size_t len, t_rng *rng, uint8_t opts)
{
	int			i;
	int			q;

	if (!seeding(rng))
		return (NULL);
	q = len / 8;
	i = -1;
	while (++i < q)
		des3_ctr((uint8_t *)dest + i * 8, 8, rng, opts & 1);
	des3_ctr((uint8_t *)dest + i * 8, len % 8, rng, opts);
	return (dest);
}
