/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecb3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:14:44 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:06:33 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					ecb3_e(t_parse *p, int64_t q)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < q + 1)
	{
		v = *((uint64_t *)p->r.msg + i);
		v = des3_block_e(v, &p->s);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}

int					ecb3_d(t_parse *p, int64_t q)
{
	uint64_t	v;
	int64_t		i;

	i = -1;
	while (++i < q)
	{
		v = *((uint64_t *)p->r.msg + p->i[1] + i);
		v = des3_block_d(v, &p->s);
		ft_memcpy(p->w.msg + p->w.len, &v, 8);
		p->w.len += 8;
	}
	return (0);
}
