/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ouxX_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:50:55 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 10:37:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_param(char *param, t_spe *sp)
{
	param[1] = 0;
	if (sp->type == 'o')
		param[0] = 8;
	else if (sp->type == 'u')
		param[0] = 10;
	else if (sp->type == 'x')
		param[0] = 16;
	else if (sp->type == 'X')
	{
		param[0] = 16;
		param[1] = 1;
	}
}

static void		size(uintmax_t i, t_spe *sp, char *param)
{
	char	*buff;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	if (!sp->size)
		putbnbr_buffer((unsigned int)i, param, buff);
	else if (!ft_memcmp(&sp->size, "H", 1))
		putbnbr_buffer((unsigned char)i, param, buff);
	else if (!ft_memcmp(&sp->size, "h", 1))
		putbnbr_buffer((unsigned short)i, param, buff);
	else if (!ft_memcmp(&sp->size, "l", 1))
		putbnbr_buffer((unsigned long)i, param, buff);
	else if (!ft_memcmp(&sp->size, "L", 1))
		putbnbr_buffer((unsigned long long)i, param, buff);
	else if (!ft_memcmp(&sp->size, "j", 1))
		putbnbr_buffer((uintmax_t)i, param, buff);
	else if (!ft_memcmp(&sp->size, "z", 1))
		putbnbr_buffer((size_t)i, param, buff);
	ft_revstr(buff);
}

static void		preci(t_spe *sp)
{
	char	*buff;
	int		p;

	if (sp->pre != -1)
	{
		buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
		if (sp->pre == 0 && buff[0] == '0')
			buff[0] = '\0';
		else
		{
			p = sp->pre - ft_strlen(buff);
			if (p > 0)
				add_nose(p, '0', buff);
		}
	}
}

static void		width_and_flags(t_spe *sp)
{
	char	*buff;
	char	offset;
	int		w;
	char	c;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	offset = 0;
	if (sp->fl.hash && sp->type == 'o' &&
			buff[0] != '0' && (offset = 1))
		add_nose(1, '0', buff);
	else if (sp->fl.hash && ((c = sp->type) == 'x' || c == 'X')
			&& ((buff[0] != '\0' && ft_hexatoi(buff) != 0)
			|| sp->fl.hash == 2) && (offset = 2))
	{
		add_nose(1, c, buff);
		add_nose(1, '0', buff);
	}
	w = sp->w - ft_strlen(buff);
	if (w > 0 && sp->fl.min)
		add_nose(w, ' ', buff + ft_strlen(buff));
	else if (w > 0 && sp->fl.ze)
		add_nose(w, '0', buff + offset);
	else if (w > 0)
		add_nose(w, ' ', buff);
}

void			oux_conv(va_list *va, t_spe *sp)
{
	char			param[2];
	uintmax_t		i;

	sp->fl.ze = (sp->pre != -1) ? 0 : sp->fl.ze;
	set_param(param, sp);
	i = va_arg(*va, uintmax_t);
	oux_malloc(i, param[0], sp);
	size(i, sp, param);
	preci(sp);
	width_and_flags(sp);
	write_spe(sp);
}
