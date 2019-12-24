/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undefined_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:03:16 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 09:55:45 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_width_flags(t_spe *sp)
{
	char	*buff;
	int		w;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	w = sp->w - ft_strlen(buff);
	if (sp->fl.ze && w > 0)
		add_nose(w, '0', buff);
	else if (w > 0)
	{
		if (!sp->fl.min)
			add_nose(w, ' ', buff);
		else
			ft_revstr(add_nose(w, ' ', ft_revstr(buff)));
	}
}

void			undefined_conv(va_list *va, t_spe *sp)
{
	int		k;
	char	*buff;

	(void)va;
	if (!sp->out)
	{
		k = MARGE;
		k = (sp->w >= k) ? sp->w : k;
		if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
			ft_exit("probleme de memoire via s_malloc\n");
		ft_memset(sp->buff.b, '\0', k + 1);
	}
	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	buff[0] = sp->type;
	ft_width_flags(sp);
	write_spe(sp);
}
