/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:41:01 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 06:49:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		end_e(t_parse *p, int64_t i)
{
	uint32_t	x;
	int8_t		re;

	re = p->r.len % 3;
	if (re != 0)
	{
		x = 0;
		ft_memcpy(&x, (uint32_t *)(p->r.msg + 3 * i), re);
		x = b64_block_e(x, re, p->s.endian);
		ft_memcpy(p->w.msg + p->w.len, &x, 4);
		p->w.len += 4;
	}
	if (p->w.len % 65 != 0)
	{
		p->w.msg[p->w.len] = '\n';
		p->w.len++;
	}
}

int				run_b64_e(t_parse *p)
{
	uint32_t	x;
	int64_t		qu;
	int64_t		i;

	qu = p->r.len / 3;
	if (!(p->w.msg = (char *)ft_memalloc(sizeof(char)
					* (4 * (qu + 1) + (4 * (qu + 1)) / 64 + 1))))
		return (-2);
	p->w.len = 0;
	i = -1;
	while (++i < qu)
	{
		x = b64_block_e(*(uint32_t *)(p->r.msg + 3 * i), 3, p->s.endian);
		ft_memcpy(p->w.msg + p->w.len, &x, 4);
		p->w.len += 4;
		if (p->w.len % 65 == 64)
		{
			p->w.msg[p->w.len] = '\n';
			p->w.len++;
		}
	}
	end_e(p, i);
	return (0);
}

int				run_b64_d(t_parse *p)
{
	uint32_t	x;
	int64_t		qu;
	int64_t		i;
	uint8_t		k;

	del_whitespaces(&p->r);
	qu = p->r.len / 4;
	if (!(p->w.msg = (char *)ft_memalloc(sizeof(char) * 3 * qu)))
		return (-2);
	p->w.len = 0;
	i = -1;
	while (++i < qu)
	{
		if ((x = b64_block_d(*(uint32_t *)(p->r.msg + 4 * i),
						&k, p->s.endian))
				== 0xFFFFFFFF)
			return (0);
		ft_memcpy(p->w.msg + p->w.len, &x, k);
		p->w.len += k;
	}
	return (0);
}

int				b64(t_parse *p)
{
	int			ret;

	if (p->out_file)
		p->w.fd = open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		p->w.fd = 1;
	if (p->w.fd == -1
		&& ft_dprintf(2, "%sout_file opening error\n%s", KRED, KNRM))
		return (0);
	ret = (p->s.o[1]) ? run_b64_d(p)
		: run_b64_e(p);
	if (ret == -2)
		return (0);
	write(p->w.fd, p->w.msg, p->w.len);
	free_p(p);
	return (ret);
}
