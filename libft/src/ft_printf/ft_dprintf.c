/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:54:44 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:55:29 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		init(int fd, t_spe *sp)
{
	sp->buff.b = NULL;
	sp->buff.ret = 0;
	sp->out = NULL;
	sp->fd = fd;
	sp->c_null_conv = 0;
}

int				ft_dprintf(int fd, const char *format, ...)
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

	init(fd, &sp);
	va_start(va, format);
	ret = conv(&sp, format, &va, tab);
	va_end(va);
	return (ret);
}
