/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:24:31 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 12:30:06 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_bin_memory(void *p, char *unit, int64_t len)
{
	char		*cptr;
	int64_t		i;

	cptr = (char *)p;
	i = -1;
	if (!ft_strcmp("byte", unit))
		while (++i < len)
			ft_printf("%u <-> %b", i, cptr[i]);
	if (!ft_strcmp("32bits-word", unit))
	{
		while (++i < len)
		{
			ft_printf("%u <-> %b", i, cptr[4 * i]);
			ft_printf("%6s%b", "<-> ", cptr[4 * i + 1]);
			ft_printf("%6s%b", "<-> ", cptr[4 * i + 2]);
			ft_printf("%6s%b", "<-> ", cptr[4 * i + 3]);
		}
	}
}

void	print_hex_memory(void *p, char *unit, int64_t len)
{
	char		*cptr;
	int64_t		i;

	cptr = (char *)p;
	i = -1;
	if (!ft_strcmp("byte", unit))
		while (++i < len)
			ft_printf("%u <-> %02x\n", i, 0xff & *(cptr + i));
	else if (!ft_strcmp("32bits-word", unit))
	{
		while (++i < len)
		{
			ft_printf("%u <-> %02x\n", i, 0xff & *(cptr + 4 * i));
			ft_printf("%6s%02x\n", "<-> ", 0xff & *(cptr + 4 * i + 1));
			ft_printf("%6s%02x\n", "<-> ", 0xff & *(cptr + 4 * i + 2));
			ft_printf("%6s%02x\n", "<-> ", 0xff & *(cptr + 4 * i + 3));
		}
	}
}
