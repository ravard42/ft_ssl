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

static void		put_hex_digit(uint8_t x)
{
	if (x < 10)
		ft_putchar('0' + x);
	else if (x >= 10 && x < 16)
		ft_putchar('a' + x - 10);
}

void			ft_puthex(void *p, int64_t len, bool newline)
{
	uint8_t		*p_8;
	int64_t		i;

	p_8 = (uint8_t *)p;
	i = -1;
	while (++i < len)
	{
		put_hex_digit(p_8[i] >> 4);
		put_hex_digit(p_8[i] & 0x0F);
	}
	if (newline)
		ft_putchar('\n');
}
