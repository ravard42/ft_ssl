/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_multi_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:33:19 by ravard            #+#    #+#             */
/*   Updated: 2018/10/13 14:33:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			is_white(char c)
{
	if (c == '\n' || c == '\v' || c == ' ' ||
			c == '\t' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

static void			all_white_to_space(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (is_white(str[i]))
			str[i] = ' ';
	}
}

char				*rm_multi_whitespace(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	all_white_to_space(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			tmp = str + i + 1;
			j = -1;
			while (tmp[++j] == ' ')
				;
			ft_strcpy(tmp, tmp + j);
		}
	}
	return (str);
}
