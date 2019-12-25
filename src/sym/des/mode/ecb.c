/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:40 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 16:16:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					ecb_e(t_parse *p, int64_t q)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < q + 1)
	{
		v = des_block_e(*((uint64_t *)p->r.msg + i), p);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}

int					ecb_d(t_parse *p, int64_t q)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < q)
	{
		v = *((uint64_t *)p->r.msg + p->i[1] + i);
		v = des_block_d(v, p);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}