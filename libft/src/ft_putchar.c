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

void			ft_putchar(int fd, char c)
{
	int	i;

	i = write(fd, &c, 1);
	(void)i;
}

void			ft_putnchar(int fd, char *ptr, size_t len)
{
	int	i;

	i = write(fd, ptr, len);
	(void)i;
}
