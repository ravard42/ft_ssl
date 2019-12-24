/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 02:24:19 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 09:56:28 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		width_and_flags(t_spe *sp)
{
	char	*buff;
	char	offset;
	int		w;
	char	c;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	offset = (buff[0]) ? ft_strlen(buff) : 1;
	w = sp->w - offset;
	if (w > 0)
	{
		if (sp->fl.min)
			add_tail(w, ' ', buff + offset);
		else
		{
			c = (sp->fl.ze) ? '0' : ' ';
			add_nose(w, c, buff);
		}
	}
}

static int		verif(wchar_t c)
{
	if (c > 255)
		return (-1);
	return (1);
}

void			c_conv(va_list *va, t_spe *sp)
{
	char			utf_8[5];
	wchar_t			c;
	char			nb_char;
	char			*buff;

	ft_memset(utf_8, '\0', 5);
	c = va_arg(*va, wchar_t);
	nb_char = (sp->size == 'l' && MB_CUR_MAX == 4) ?
		utf_32_to_8(c, utf_8) : verif(c);
	if (nb_char == -1 && (sp->size = -42))
		return ;
	c_malloc(nb_char, sp);
	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	sp->c_null_conv = (!c) ? 1 : 0;
	if (c && sp->size == 'l' && MB_CUR_MAX == 4)
		putstr_buffer(utf_8, buff);
	else if (c)
		putchar_buffer(c, buff);
	width_and_flags(sp);
	write_spe(sp);
	sp->c_null_conv = 0;
}
