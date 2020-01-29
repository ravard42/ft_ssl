/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:46:42 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:46:57 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool		ft_is_decimal(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = -1;
	while (str[++i] && str[i] >= '0' && str[i] <= '9')
		;
	if (str[i])
		return (false);
	return (true);
}
