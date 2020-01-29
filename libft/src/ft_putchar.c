/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:44:32 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:48:01 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putchar(char c)
{
	int	i;

	i = write(1, &c, 1);
	(void)i;
}

void			ft_putnchar(char *ptr, size_t len)
{
	int	i;

	i = write(1, ptr, len);
	(void)i;
}
