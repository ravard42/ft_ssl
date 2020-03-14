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

static void		put_hex_digit(uint8_t x, bool capitalize)
{
	char	a;

	a = (capitalize) ? 'A' : 'a';
	if (x < 10)
		ft_putchar('0' + x);
	else if (x >= 10 && x < 16)
		ft_putchar(a + x - 10);
}

void			ft_puthex(void *p, int64_t len, bool capitalize, bool newline)
{
	uint8_t		*p_8;
	int64_t		i;

	p_8 = (uint8_t *)p;
	i = -1;
	while (++i < len)
	{
		put_hex_digit(p_8[i] >> 4, capitalize);
		put_hex_digit(p_8[i] & 0x0F, capitalize);
	}
	if (newline)
		ft_putchar('\n');
}

void			ft_putrhex(void *p, int64_t len, bool capitalize, bool newline)
{
	uint8_t		*p_8;
	int64_t		i;

	p_8 = (uint8_t *)p;
	i = len;
	while (--i >= 0)
	{
		put_hex_digit(p_8[i] >> 4, capitalize);
		put_hex_digit(p_8[i] & 0x0F, capitalize);
	}
	if (newline)
		ft_putchar('\n');
}
