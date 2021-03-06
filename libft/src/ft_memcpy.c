/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 23:58:46 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:47:05 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** WARNING:  dst and src must not overlap! (cf ft_memshift for that)
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (str1);
}

void	*ft_memrcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	i = -1;
	while (++i < n)
		str1[i] = str2[n - 1 - i];
	return (str1);
}
