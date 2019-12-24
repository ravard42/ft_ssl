/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/17 00:07:39 by ravard            #+#    #+#             */
/*   Updated: 2016/01/17 00:07:52 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	d;
	int		i;

	str = (char *)s;
	d = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == d)
			return (str + i);
		else
			i++;
	}
	if (str[i] == '\0' && d == '\0')
		return (str + i);
	else
		return (NULL);
}
