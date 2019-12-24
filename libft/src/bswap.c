/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bswap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:43:41 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 12:20:59 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t		bswap32(uint32_t x)
{
	uint8_t	tmp;
	uint8_t	rev[4];
	uint8_t	i;

	ft_memcpy(rev, &x, 4);
	i = -1;
	while (++i < 2)
	{
		tmp = rev[i];
		rev[i] = rev[3 - i];
		rev[3 - i] = tmp;
	}
	x = *((uint32_t *)rev);
	return (x);
}

uint32_t		*multi_bswap32(uint32_t *h, int64_t size)
{
	int	i;

	i = -1;
	while (++i < size)
		h[i] = bswap32(h[i]);
	return (h);
}

uint64_t		bswap64(uint64_t x)
{
	uint8_t	tmp;
	uint8_t	rev[8];
	uint8_t	i;

	ft_memcpy(rev, &x, 8);
	i = -1;
	while (++i < 4)
	{
		tmp = rev[i];
		rev[i] = rev[7 - i];
		rev[7 - i] = tmp;
	}
	x = *((uint64_t *)rev);
	return (x);
}

uint64_t		*multi_bswap64(uint64_t *h, int64_t size)
{
	int	i;

	i = -1;
	while (++i < size)
		h[i] = bswap64(h[i]);
	return (h);
}
