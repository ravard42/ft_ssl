/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cfb3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:49 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 16:20:02 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					cfb3_e(t_parse *p, int64_t q)
{
	uint64_t	v[2];
	int8_t		r;
	int64_t		i;

	r = p->r.len % 8;
	v[0] = *p->s.arg[1].x;
	i = -1;
	while (++i < q)
	{
		v[0] = des_triple(v[0], p) ^ *((uint64_t *)p->r.msg + i);
		ft_memcpy(p->w.msg + p->w.len, v, 8);
		p->w.len += 8;
	}
	ft_memcpy(v + 1, (uint64_t *)p->r.msg + p->i[1] + i, r);
	v[1] ^= des_triple(v[0], p);
	ft_memcpy(p->w.msg + p->w.len, v + 1, r);
	p->w.len += r;
	return (0);
}

int					cfb3_d(t_parse *p, int64_t q)
{
	uint64_t	v[2];
	int64_t		r;
	int64_t		i;

	r = p->r.len % 8;
	v[0] = *p->s.arg[1].x;
	i = -1;
	while (++i < q)
	{
		v[1] = *((uint64_t *)p->r.msg + p->i[1] + i);
		v[0] = des_triple(v[0], p) ^ v[1];
		ft_memcpy(p->w.msg + p->w.len, v, 8);
		p->w.len += 8;
		v[0] = v[1];
	}
	ft_memcpy(v + 1, (uint64_t *)p->r.msg + p->i[1] + i, r);
	v[1] ^= des_triple(v[0], p);
	ft_memcpy(p->w.msg + p->w.len, v + 1, r);
	p->w.len += r;
	return (0);
}
