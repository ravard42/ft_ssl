/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:44:46 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:54:41 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char		is_prime(uint64_t p)
{
	uint64_t i;

	if (p < 2)
		return (0);
	i = 1;
	while (++i != p)
		if (p % i == 0)
			break ;
	i = (p == i) ? 1 : 0;
	return (i);
}

static void		load_prim_tab(uint32_t *p)
{
	int		n;
	int		i;

	n = 1;
	p[0] = 2;
	while (n != 64)
	{
		i = p[n - 1];
		while (!is_prime(++i))
			;
		p[n] = i;
		n++;
	}
}

void			sha256_init(t_hash *hash)
{
	uint32_t	p[64];
	int64_t		i;
	double		d;

	load_prim_tab(p);
	i = -1;
	while (++i < 64)
	{
		if (i < 8)
		{
			d = pow(p[i], 1 / (double)2);
			d -= floor(d);
			hash->h[i] = floor(d * pow(16, 8));
		}
		d = pow(p[i], 1 / (double)3);
		d -= floor(d);
		hash->k[i] = floor(d * pow(16, 8));
	}
}
