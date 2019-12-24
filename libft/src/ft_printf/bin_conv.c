/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:29:12 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 14:12:47 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		bin_disp_char(char c, char *buff)
{
	size_t	k;

	k = -1;
	while (++k < 8)
		putchar_buffer('0' + (c >> k & 1), buff + 7 - k);
	putchar_buffer('\n', buff + 8);
}

static void		bin_disp(int val, size_t len, t_spe *sp)
{
	char		*tmp;
	size_t		i;
	char		*buff;

	buff = (!sp->out) ? sp->buff.b : sp->out + sp->buff.ret;
	tmp = (char *)&val;
	i = -1;
	while (++i < len)
		bin_disp_char(tmp[i], buff + 9 * i);
}

void			bin_conv(va_list *va, t_spe *sp)
{
	int		k;
	char	nb_char;

	nb_char = 1;
	if (sp->size == 'h')
		nb_char = 2;
	else if (sp->size == 'l')
		nb_char = 4;
	if (!sp->out)
	{
		k = nb_char * 9 + MARGE;
		if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
			ft_exit("probleme de memoire via bin_malloc\n");
		ft_memset(sp->buff.b, '\0', k + 1);
	}
	bin_disp(va_arg(*va, int), nb_char, sp);
	write_spe(sp);
}
