/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:49:21 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 20:50:40 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		toupper_stdout(char *str)
{
	int		rw;
	int		i;
	char	tmp;

	(void)rw;
	i = -1;
	while (str[++i])
	{
		if ((tmp = str[i] - 'a' + 'A') >= 'A' && tmp <= 'Z')
			rw = write(1, &tmp, 1);
		else
			rw = write(1, str + i, 1);
	}
}

static void		handle_opts(t_parse *p, t_hash *hash)
{
	char	ternary;

	(void)ternary;
	if (p->h.o[2])
		ft_puthex(1, hash->h, p->cmd.hash_hex_len, 5);
	else
	{
		if (!p->h.o[3])
		{
			toupper_stdout(p->cmd.name);
			ternary = (p->h.o[4]) ? ft_printf("(\"%s\")= ", p->r.msg)
				: ft_printf("(%s)= ", p->in_file);
			ft_puthex(1, hash->h, p->cmd.hash_hex_len, 5);
		}
		else
		{
			ft_puthex(1, hash->h, p->cmd.hash_hex_len, 4);
			ternary = (p->h.o[4]) ? ft_printf(" \"%s\"\n", p->r.msg)
				: ft_printf(" %s\n", p->in_file);
		}
	}
}

void			print_format(t_parse *p, t_hash *hash)
{
	if (p->h.o[4] || p->in_file)
		handle_opts(p, hash);
	else
	{
		if (p->h.o[1])
			ft_printf("%s", p->r.msg);
		ft_puthex(1, hash->h, p->cmd.hash_hex_len, 5);
	}
	p->i[2]++;
	p->h.o[0] = (p->in_file) ? 1 : 0;
	p->h.o[1] = 0;
	p->h.o[4] = 0;
}
