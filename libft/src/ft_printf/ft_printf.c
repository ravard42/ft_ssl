/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 02:11:31 by ravard            #+#    #+#             */
/*   Updated: 2018/03/09 14:33:48 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init(t_spe *sp)
{
	sp->buff.b = NULL;
	sp->buff.ret = 0;
	sp->out = NULL;
	sp->fd = 1;
	sp->c_null_conv = 0;
}

int	ft_printf(const char *format, ...)
{
	static t_conv const	tab[] = {{"c", &c_conv},
								{"s", &s_conv},
								{"di", &d_conv},
								{"ouxX", &oux_conv},
								{"b", &bin_conv},
								{"", &undefined_conv}};
	va_list				va;
	int					ret;
	t_spe					sp;

	init(&sp);
	va_start(va, format);
	ret = conv(&sp, format, &va, tab);
	va_end(va);
	return (ret);
}
