/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:40 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:05:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					ecb_e(t_parse *p)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < p->r.len / 8)
	{
		v = des_block_e(*((uint64_t *)p->r.msg + i), &p->s);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}

int					ecb_d(t_parse *p)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < p->r.len / 8 - p->i[1])
	{
		v = *((uint64_t *)p->r.msg + p->i[1] + i);
		v = des_block_d(v, &p->s);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}
