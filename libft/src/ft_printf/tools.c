/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:39:46 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 08:01:27 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_exit(char *error)
{
	ft_putstr(error);
	exit(0);
}


void			init_spe(t_spe *sp)
{
	sp->fl.hash = 0;
	sp->fl.min = 0;
	sp->fl.plu = 0;
	sp->fl.sp = 0;
	sp->fl.ze = 0;
	sp->w = -1;
	sp->pre = -1;
	sp->size = '\0';
	sp->type = '\0';
}

int				catch_pos_numb(char *s)
{
	int		i;
	char	buff[32];

	i = -1;
	while (s[++i] >= '0' && s[i] <= '9')
	{
		if (i >= 31)
			ft_exit("who dare brutalise my printouf?!\n");
		buff[i] = s[i];
	}
	buff[i] = '\0';
	return (ft_atoi(buff));
}

char			*add_nose(int nb, char c, char *buff)
{
	int		len;
	int		i;

	len = ft_strlen(buff);
	i = len;
	while (--i >= 0)
		buff[nb + i] = buff[i];
	i = -1;
	while (++i < nb)
		buff[i] = c;
	return (buff);
}

char			*add_tail(int nb, char c, char *buff)
{
	int		i;

	i = -1;
	while (++i < nb)
		buff[i] = c;
	return (buff);
}

