/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:27:26 by ravard            #+#    #+#             */
/*   Updated: 2018/03/10 19:43:17 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			putchar_buffer(char c, char *buff)
{
	*buff = c;
}

void			putstr_buffer(char *str, char *buff)
{
	int	i;

	i = -1;
	if (str)
		while (str[++i])
			putchar_buffer(str[i], buff + i);
}

void			putnbr_buffer(intmax_t n, char *buff)
{
	if (n < 0)
	{
		if (n == INTMAX_MIN)
			putstr_buffer("-9223372036854775808", buff);
		else
		{
			putchar_buffer('-', buff);
			putnbr_buffer(-n, buff + 1);
		}
	}
	else if (n >= 0 && n < 10)
		putchar_buffer('0' + n, buff);
	else
	{
		putnbr_buffer(n / 10, buff + 1);
		putnbr_buffer(n % 10, buff);
	}
}

static void		putbdigit_buffer(char n, char *param, char *buff)
{
	char	c;

	c = param[1] ? 'A' : 'a';
	if (n < 10)
		putchar_buffer('0' + n, buff);
	else
		putchar_buffer(c + n - 10, buff);
}

void			putbnbr_buffer(uintmax_t n, char *param, char *buff)
{
	if (param[0] > 35)
		*buff = '\0';
	else if (n < (uintmax_t)param[0])
		putbdigit_buffer(n, param, buff);
	else
	{
		putbnbr_buffer(n / param[0], param, buff + 1);
		putbnbr_buffer(n % param[0], param, buff);
	}
}
