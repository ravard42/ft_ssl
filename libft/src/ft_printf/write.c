/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:47:24 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 10:28:18 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				write_no_spe(char const *s, t_spe *sp)
{
	int		i;

	i = -1;
	while (s[++i] && s[i] != '%')
	{
		if (sp->out != NULL && (sp->out[sp->buff.ret] = s[i]))
			sp->buff.ret++;
	}
	if (sp->out == NULL)
		sp->buff.ret += write(sp->fd, s, i);
	return (i);
}

void			write_spe(t_spe *sp)
{
	if (sp->out == NULL)
	{
		if (sp->c_null_conv)
			sp->buff.ret += (sp->w >= 2) ? write(sp->fd, sp->buff.b, sp->w)
				: write(sp->fd, sp->buff.b, 1);
		else if (sp->size != -42)
			sp->buff.ret += write(sp->fd, sp->buff.b, ft_strlen(sp->buff.b));
		free(sp->buff.b);
		sp->buff.b = NULL;
	}
	else
	{
		if (sp->c_null_conv)
			sp->buff.ret += (sp->w >= 2) ? sp->w : 1;
		else
			sp->buff.ret += ft_strlen(sp->out + sp->buff.ret);
	}
}
