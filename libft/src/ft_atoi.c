/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:32:10 by ravard            #+#    #+#             */
/*   Updated: 2018/10/13 14:31:43 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*polarity(char *str, int *sign)
{
	if (str[0] == '-')
	{
		*sign = -1;
		return (str + 1);
	}
	else if (str[0] == '+')
	{
		*sign = 1;
		return (str + 1);
	}
	else
	{
		*sign = 1;
		return (str);
	}
}

int			ft_len(char *buf, char mode)
{
	int	i;

	i = 0;
	if (mode == 0)
	{
		while (buf[i] >= '0' && buf[i] <= '9')
			i++;
	}
	else if (mode == 1)
	{
		while ((buf[i] >= '0' && buf[i] <= '9')
				|| (buf[i] >= 'a' && buf[i] <= 'f')
				|| (buf[i] >= 'A' && buf[i] <= 'F'))
			i++;
	}
	return (i);
}

int			ft_power(int x, int n)
{
	int	i;
	int	ret;

	ret = 1;
	i = 0;
	while (++i <= n)
		ret *= x;
	return (ret);
}

int			ft_atoi(const char *str)
{
	char	*buf;
	int		sign;
	int		i[2];
	int		result;

	buf = polarity(rm_begin_whitespace((char *)str), &sign);
	i[0] = -1;
	i[1] = ft_len(buf, 0);
	result = 0;
	while (++i[0] < i[1])
		result += (buf[i[0]] - '0') * ft_power(10, i[1] - i[0] - 1);
	result = sign * result;
	return (result);
}

int			ft_hexatoi(const char *str)
{
	char	*buf;
	int		i[2];
	int		result;

	buf = rm_begin_whitespace((char *)str);
	i[0] = -1;
	i[1] = ft_len(buf, 1);
	result = 0;
	while (++i[0] < i[1])
		result += (buf[i[0]] >= '0' && buf[i[0]] <= '9') ?
			(buf[i[0]] - '0') * ft_power(16, i[1] - i[0] - 1) :
			(buf[i[0]] - 'a' + 10) * ft_power(16, i[1] - i[0] - 1);
	return (result);
}
