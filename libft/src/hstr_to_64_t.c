/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hstr_to_64_t.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:53:09 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:54:07 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

static int			verif(char *buff, int64_t len, char *str)
{
	int	i;

	i = -1;
	while (str[++i] && i < len)
	{
		buff[i] = ft_toupper(str[i]);
		if ((buff[i] < '0' || buff[i] > '9')
			&& (buff[i] < 'A' || buff[i] > 'F')
			&& ft_dprintf(2, "%sERROR : hexadecimal string is expected\n%s",
				KRED, KNRM))
			return (-1);
	}
	if (i != len)
	{
		ft_dprintf(2, "%shex string is too short, \
padding with zero bytes to length%s\n", KYEL, KNRM);
		return (i);
	}
	else if (ft_strlen(str) > (uint64_t)len)
		ft_dprintf(2, "%stoo long hex string, ignoring excess%s\n", KYEL, KNRM);
	return (len);
}

static uint8_t		hstr_to_8_t(char *str, int lim)
{
	uint8_t	ret;
	int		i;

	ret = 0;
	i = -1;
	while (++i < lim)
		ret += (str[i] >= '0' && str[i] <= '9') ?
			(str[i] - '0') << 4 * (1 - i)
			: (str[i] - 'A' + 10) << 4 * (1 - i);
	return (ret);
}

static void			load_x(uint64_t *x, int64_t len, char *str)
{
	int	q;
	int	r;
	int	i;

	q = len / 2;
	r = len % 2;
	i = -1;
	while (++i < q)
		*((uint8_t *)x + i) = hstr_to_8_t(str + 2 * i, 2);
	if (r)
		*((uint8_t *)x + i) = hstr_to_8_t(str + 2 * i, r);
}

/*
** if (x == NULL) => on alloue dynamiquement la mémoire
** if (x != NULL) => on fait confiance à l'utilisateur
**							pour fournir une zone mémoire pouvant
**							accueillir au moins len_64 * 8 bytes
**							(sinon segfault ...)
*/

uint64_t			*hstr_to_64_t(uint64_t *x, int64_t len_64, char *str)
{
	char		buff[len_64 * 8 * 2];
	int64_t		len;

	ft_memset(buff, 0, len_64 * 8 * 2);
	if ((len = verif(buff, len_64 * 8 * 2, str)) == -1)
		return (NULL);
	if (x == NULL && !(x = (uint64_t *)ft_memalloc(sizeof(uint64_t) * len_64)))
		return (NULL);
	else
		ft_memset((char *)x, 0, len_64 * 8);
	load_x(x, len, buff);
	return (x);
}
