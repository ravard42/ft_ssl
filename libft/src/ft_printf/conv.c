/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:48:06 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 09:25:24 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	exception(t_spe *sp)
{
	char	c;

	if ((c = sp->type) == 'D' || c == 'O' || c == 'U' || c == 'p'
			|| c == 'C' || c == 'S')
	{
		sp->size = 'l';
		if (sp->type == 'D' && (sp->type = 'd'))
			return (2);
		else if (sp->type == 'O' && (sp->type = 'o'))
			return (3);
		else if (sp->type == 'U' && (sp->type = 'u'))
			return (3);
		else if (sp->type == 'p' && (sp->type = 'x'))
		{
			sp->fl.hash = 2;
			return (3);
		}
		else if (sp->type == 'C' && (sp->type = 'c'))
			return (0);
		else if (sp->type == 'S' && (sp->type = 's'))
			return (1);
	}
	return (-1);
}

static int	select_conv(t_conv const *tab, t_spe *sp)
{
	int		i;
	int		j;

	if ((i = exception(sp)) != -1)
		return (i);
	while (tab[++i].s[0])
	{
		j = -1;
		while (tab[i].s[++j] && tab[i].s[j] != sp->type)
			;
		if (tab[i].s[j] && tab[i].s[j] == sp->type)
			return (i);
	}
	return (i);
}

int			conv(t_spe *sp, const char *s, va_list *va, t_conv const *tab)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '%')
			i += write_no_spe(s + i, sp);
		if (s[i] == '%')
		{
			i += extract_specifier(s + i + 1, sp);
			tab[select_conv(tab, sp)].f(va, sp);
		}
		if (sp->size == -42 && (sp->buff.ret = -1))
			break ;
	}
	return (sp->buff.ret);
}
