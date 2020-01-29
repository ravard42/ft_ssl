/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:58:24 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:52:54 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	if (!str
		&& ft_dprintf(2, "%sft_strdup(NULL), NULL returned%s\n", KYEL, KNRM))
		return (NULL);
	if (!(dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1)))
		&& ft_dprintf(2, "%smalloc error in ft_strdup%s\n", KRED, KNRM))
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
