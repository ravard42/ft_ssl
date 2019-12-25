/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:14 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 16:20:40 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					cbc_e(t_parse *p, int64_t q)
{
	uint64_t	v[2];
	int64_t		i;

	v[0] = *p->s.arg[1].x;
	i = -1;
	while (++i < q + 1)
	{
		v[0] = des_block_e(*((uint64_t *)p->r.msg + i) ^ v[0], p);
		ft_memcpy(p->w.msg + p->w.len, v, 8);
		p->w.len += 8;
	}
	return (0);
}

int					cbc_d(t_parse *p, int64_t q)
{
	uint64_t	v[2];
	int64_t		i;

	v[0] = *p->s.arg[1].x;
	i = -1;
	while (++i < q)
	{
		v[1] = *((uint64_t *)p->r.msg + p->i[1] + i);
		v[0] = des_block_d(v[1], p) ^ v[0];
		ft_memcpy(p->w.msg + p->w.len, v, 8);
		p->w.len += 8;
		v[0] = v[1];
	}
	return (0);
}
