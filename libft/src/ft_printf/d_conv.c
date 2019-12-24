/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:49:42 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 09:24:23 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			size(intmax_t i, t_spe *sp)
{
	char	*buff;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	if (!sp->size)
		putnbr_buffer((int)i, buff);
	else if (!ft_memcmp(&sp->size, "H", 1))
		putnbr_buffer((char)i, buff);
	else if (!ft_memcmp(&sp->size, "h", 1))
		putnbr_buffer((short)i, buff);
	else if (!ft_memcmp(&sp->size, "l", 1))
		putnbr_buffer((long)i, buff);
	else if (!ft_memcmp(&sp->size, "L", 1))
		putnbr_buffer((long long)i, buff);
	else if (!ft_memcmp(&sp->size, "j", 1))
		putnbr_buffer((intmax_t)i, buff);
	else if (!ft_memcmp(&sp->size, "z", 1))
		putnbr_buffer((ssize_t)i, buff);
	if (buff[0] == '-' && i != INTMAX_MIN)
		ft_revstr(buff + 1);
	else if (i != INTMAX_MIN)
		ft_revstr(buff);
}

static void			preci(t_spe *sp)
{
	char	*buff;
	int		offset;
	int		p;

	if (sp->pre != -1)
	{
		buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
		if (sp->pre == 0 && buff[0] == '0')
			buff[0] = '\0';
		else
		{
			offset = (buff[0] == '-') ? 1 : 0;
			p = sp->pre - ft_strlen(buff + offset);
			if (p > 0)
				add_nose(p, '0', buff + offset);
		}
	}
}

static int			set_offset(char c, char *buff)
{
	if (c == ' ')
		return (0);
	if (c == '0' && (buff[0] >= '0' && buff[0] <= '9'))
		return (0);
	return (1);
}

static void			width_and_flags(t_spe *sp)
{
	char	*buff;
	int		offset;
	int		w;
	char	c;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	sp->fl.sp = (buff[0] == '-') ? 0 : sp->fl.sp;
	sp->fl.plu = (buff[0] == '-') ? 0 : sp->fl.plu;
	if (sp->fl.sp)
		add_nose(1, ' ', buff);
	else if (sp->fl.plu)
		add_nose(1, '+', buff);
	w = sp->w - ft_strlen(buff);
	if (w > 0)
	{
		if (sp->fl.min)
			add_tail(w, ' ', buff + ft_strlen(buff));
		else
		{
			c = (sp->fl.ze) ? '0' : ' ';
			offset = set_offset(c, buff);
			add_nose(w, c, buff + offset);
		}
	}
}

void				d_conv(va_list *va, t_spe *sp)
{
	intmax_t			i;

	sp->fl.ze = (sp->pre != -1) ? 0 : sp->fl.ze;
	i = va_arg(*va, intmax_t);
	d_malloc(i, sp);
	size(i, sp);
	preci(sp);
	width_and_flags(sp);
	write_spe(sp);
}
