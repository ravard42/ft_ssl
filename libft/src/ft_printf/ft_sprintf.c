/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 22:55:22 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:56:41 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		init(char *str, t_spe *sp)
{
	sp->buff.b = NULL;
	sp->buff.ret = 0;
	sp->out = str;
	sp->fd = -1;
	sp->c_null_conv = 0;
}

int				ft_sprintf(char *str, const char *format, ...)
{
	static t_conv const		tab[] = {{"c", &c_conv},
								{"s", &s_conv},
								{"di", &d_conv},
								{"ouxX", &oux_conv},
								{"b", &bin_conv},
								{"", &undefined_conv}};
	va_list					va;
	int						ret;
	t_spe					sp;

	init(str, &sp);
	va_start(va, format);
	ret = conv(&sp, format, &va, tab);
	va_end(va);
	return (ret);
}
