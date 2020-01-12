/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:25 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 11:16:36 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int			malloc_e(t_parse *p, int64_t q)
{
	if (p->s.arg[2].set)
	{
		if (!(p->w.msg = (char *)ft_memalloc(sizeof(char) * 8 * (q + 3))))
			return (-2);
		ft_memcpy(p->w.msg, "Salted__", 8);
		ft_memcpy(p->w.msg + 8, &p->s.arg[2].x, 8);
	}
	else if (!(p->w.msg = (char *)ft_memalloc(sizeof(char) * 8 * (q + 1))))
		return (-2);
	return (1);
}

static int			enc(t_parse *p, int64_t q)
{
	if (p->cmd.needed[2] && !des_padding(p, q))
		return (0);
	if (malloc_e(p, q) == -2)
		return (0);
	p->w.len = (p->s.arg[2].set) ? 16 : 0;
	p->cmd.run_e(p, q);
	return (1);
}

static int			dec(t_parse *p, int64_t q)
{
	if (!(p->w.msg = (char *)ft_memalloc(sizeof(char) * 8 * (q + 1))))
		return (0);
	p->w.len = 0;
	p->cmd.run_d(p, q);
	if (p->cmd.needed[2] && p->w.len / 8 >= 1 && p->w.len % 8 == 0)
		p->w.len -= des_unpadding(&p->w);
	return (1);
}

int					des(t_parse *p)
{
	int64_t		q;

	if (!check_out(p))
		return (0);
	if (p->s.o[1] && p->s.o[4] && !opt_a_d(p))
		return (0);
	if (!check_k_v(p))
		return (0);
	q = p->r.len / 8 - p->i[1];
	if (!p->s.o[1] && !enc(p, q))
		return (0);
	else if (p->s.o[1] && !dec(p, q))
		return (0);
	if (!p->s.o[1] && p->s.o[4] && !opt_a_e(p))
		return (0);
	write(p->w.fd, p->w.msg, p->w.len);
	free_p(p);
	return (0);
}
