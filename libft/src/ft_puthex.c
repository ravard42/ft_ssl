/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:20:25 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 12:20:28 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		put_hex_digit(int fd, uint8_t x, bool capitalize)
{
	char	a;

	a = (capitalize) ? 'A' : 'a';
	if (x < 10)
		ft_putchar(fd, '0' + x);
	else if (x >= 10 && x < 16)
		ft_putchar(fd, a + x - 10);
}


static void		heading_zero(int fd, uint8_t first_byte, uint8_t opts)
{
	uint8_t tmp;

	tmp = first_byte >> 4;
	if (tmp != 0 || (opts & 4))
		put_hex_digit(fd, tmp, opts & 2);
	put_hex_digit(fd, first_byte & 0x0F, opts & 2);
}

/*
** options: heading_0 capitalize newline
**					100			010		001
*/

void			ft_puthex(int fd, void *p, int64_t len, uint8_t opts)
{
	uint8_t		*p_8;
	int64_t		i;

	p_8 = (uint8_t *)p;
	heading_zero(fd, p_8[0], opts);
	i = 0;
	while (++i < len)
	{
		put_hex_digit(fd, p_8[i] >> 4, opts & 2);
		put_hex_digit(fd, p_8[i] & 0x0F, opts & 2);
	}
	if (opts & 1)
		ft_putchar(fd, '\n');
}

void			ft_putrhex(int fd, void *p, int64_t len, uint8_t opts)
{
	uint8_t		*p_8;
	int64_t		i;

	p_8 = (uint8_t *)p;
	heading_zero(fd, p_8[len - 1], opts);
	i = len - 1;
	while (--i >= 0)
	{
		put_hex_digit(fd, p_8[i] >> 4, opts & 2);
		put_hex_digit(fd, p_8[i] & 0x0F, opts & 2);
	}
	if (opts & 1)
		ft_putchar(fd, '\n');
}
