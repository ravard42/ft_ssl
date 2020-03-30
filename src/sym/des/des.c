/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:21:25 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 00:55:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int			malloc_e(t_parse *p)
{
	if (p->s.arg[2].set)
	{
		if (!(p->w.msg = (char *)ft_memalloc(sizeof(char)
			* 8 * (p->r.len / 8 + 3))))
			return (-2);
		ft_memcpy(p->w.msg, "Salted__", 8);
		ft_memcpy(p->w.msg + 8, &p->s.arg[2].x, 8);
	}
	else if (!(p->w.msg = (char *)ft_memalloc(sizeof(char)
		* 8 * (p->r.len / 8 + 1))))
		return (-2);
	return (1);
}

int					des_enc(t_parse *p)
{
	if (p->cmd.needed[2] && !des_padding(p))
		return (0);
	if (malloc_e(p) == -2)
		return (0);
	p->w.len = (p->s.arg[2].set) ? 16 : 0;
	p->cmd.run_e(p);
	return (1);
}

int					des_dec(t_parse *p)
{
	if (!(p->w.msg = (char *)ft_memalloc(sizeof(char)
		* 8 * (p->r.len / 8 - p->i[1] + 1))))
		return (0);
	p->w.len = 0;
	p->cmd.run_d(p);
	if (p->cmd.needed[2] && p->w.len / 8 >= 1 && p->w.len % 8 == 0)
		p->w.len -= des_unpadding(&p->w);
	return (1);
}

int					des(t_parse *p)
{
	if (!check_out(p))
		return (0);
	if (p->s.o[1] && p->s.o[4] && !opt_a_d(p))
		return (0);
	if (!check_k_v(p))
		return (0);
	if (!p->s.o[1] && !des_enc(p))
		return (0);
	else if (p->s.o[1] && !des_dec(p))
		return (0);
	if (!p->s.o[1] && p->s.o[4] && !opt_a_e(p))
		return (0);
	write(p->w.fd, p->w.msg, p->w.len);
	return (0);
}
