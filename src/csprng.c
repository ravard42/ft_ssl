/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csprng.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 07:01:13 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 07:01:14 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool		reseeding(t_parse *p)
{
	int				i;
	uint64_t		buff[3];

	if (read(p->rng.fd, &buff, 24) != 24
		&& ft_dprintf(2, "%s%s%s\n", KRED, SEED_ERR, KNRM))
		return (false);
	else
	{
		ft_dprintf(2, "%sreseeding: 24 bytes (3 * uint64_t) read on p->rng%s\n", KYEL, KNRM);
		i = -1;
		while (++i < 3)
			ft_dprintf(2, "%016lx\n", buff[i]);
		sleep(3);
	}
	ft_memcpy(p->s.arg[0].x, buff, 3);
	format_key(p);
	return (true);
}

/*
** triple des csprng
** beware that dest have enough space memory for len bytes
** treshold set at 0xa00000 for reseeding (~10min)
**
** need to replace t_parse by t_rng
** which will have his own t_sym for running triple des
*/

void			*prng(void *dest, size_t len, t_parse *p)
{
	uint64_t	buff;
	int			i;
	int			q;
	int			r;

	if (p->rng.co >= 0xa00000
		&& !(p->rng.co = 0)
		&& !reseeding(p))
		return (false);
	q = len / 8;
	i = -1;
	while (++i < q)
	{
		buff = des_triple(++p->rng.co, p);
		ft_memcpy(dest, &buff, 8);
	}
	if ((r = len % 8))
	{
		buff = des_triple(++p->rng.co, p);
		ft_memcpy(dest, &buff, r);
	}
	return (dest);
}
