/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_begin_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 14:24:07 by ravard            #+#    #+#             */
/*   Updated: 2018/10/13 14:24:51 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*rm_begin_whitespace(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] == '\n' || str[i] == '\v' || str[i] == ' ' ||
			str[i] == '\t' || str[i] == '\r' || str[i] == '\f')
			i++;
		return (str + i);
	}
	return (NULL);
}
