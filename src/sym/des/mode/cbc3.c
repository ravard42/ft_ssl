/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:37 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:07:17 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					cbc3_e(t_parse *p, int64_t q)
{
	uint64_t	v;
	int64_t		i;

	v = *p->s.arg[1].x;
	i = -1;
	while (++i < q + 1)
	{
		v ^= *((uint64_t *)p->r.msg + i);
		v = des3_block_e(v, &p->s);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}

int					cbc3_d(t_parse *p, int64_t q)
{
	uint64_t	v[3];
	int64_t		i;

	v[0] = *p->s.arg[1].x;
	i = -1;
	while (++i < q)
	{
		v[1] = *((uint64_t *)p->r.msg + p->i[1] + i);
		v[2] = des3_block_d(v[1], &p->s);
		v[2] ^= v[0];
		ft_memcpy(p->w.msg + p->w.len, v + 2, 8);
		p->w.len += 8;
		v[0] = v[1];
	}
	return (0);
}
