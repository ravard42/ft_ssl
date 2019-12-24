/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_buff_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:28:07 by ravard            #+#    #+#             */
/*   Updated: 2018/03/12 09:36:07 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*buff_malloc(int *offset, char const *s, t_spe *sp)
{
	static const char	*no_type = "#-+ 0123456789.hljz";
	int					i[2];
	char				*buff;

	i[0] = -1;
	while (s[++i[0]])
	{
		i[1] = -1;
		while (no_type[++i[1]])
			if (s[i[0]] == no_type[i[1]])
				break ;
		if (!no_type[i[1]] && (sp->type = s[i[0]]))
			break ;
	}
	if (!(buff = (char *)malloc(sizeof(char) * (i[0] + 1))))
		ft_exit("probleme de memoire via buff_malloc\n");
	*offset = (sp->type) ? i[0] + 1 : i[0];
	return (buff);
}

void		d_malloc(intmax_t i, t_spe *sp)
{
	int		k;

	if (sp->out)
		return ;
	k = MARGE;
	if (i < 0)
		i = -i;
	while ((i /= 10) != 0)
		++k;
	k = (sp->pre >= k) ? sp->pre + MARGE : k;
	k = (sp->w >= k) ? sp->w + MARGE : k;
	if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
		ft_exit("probleme de memoire via d_malloc\n");
	ft_memset(sp->buff.b, '\0', k + 1);
}

void		oux_malloc(uintmax_t i, char b, t_spe *sp)
{
	int		k;

	if (sp->out)
		return ;
	k = MARGE;
	while ((i /= b) != 0)
		++k;
	k = (sp->pre >= k - 1) ? sp->pre + MARGE : k;
	k = (sp->w >= k - 1) ? sp->w + MARGE : k;
	if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
		ft_exit("probleme de memoire via oux_malloc\n");
	ft_memset(sp->buff.b, '\0', k + 1);
}

void		c_malloc(char nb_char, t_spe *sp)
{
	int		k;

	if (sp->out)
		return ;
	k = (sp->w > nb_char) ? sp->w + MARGE : MARGE;
	if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
		ft_exit("probleme de memoire via c_malloc\n");
	ft_memset(sp->buff.b, '\0', k + 1);
}

void		s_malloc(char *str, t_spe *sp)
{
	int		k;

	if (sp->out)
		return ;
	k = (str) ? ft_strlen(str) + MARGE : ft_strlen("(null)") + MARGE;
	k = (sp->w >= k) ? sp->w + MARGE : k;
	if (!(sp->buff.b = (char *)malloc(sizeof(char) * (k + 1))))
		ft_exit("probleme de memoire via s_malloc\n");
	ft_memset(sp->buff.b, '\0', k + 1);
}
