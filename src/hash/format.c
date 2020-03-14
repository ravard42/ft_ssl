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
	int		i;
	char	tmp;

	i = -1;
	while (str[++i])
	{
		if ((tmp = str[i] - 'a' + 'A') >= 'A' && tmp <= 'Z')
			write(1, &tmp, 1);
		else
			write(1, str + i, 1);
	}
}

static void		handle_opts(t_parse *p, t_hash *hash)
{
	char	ternary;

	(void)ternary;
	if (p->h.o[2])
		ft_puthex(hash->h, p->cmd.hash_hex_len, false, true);
	else
	{
		if (!p->h.o[3])
		{
			toupper_stdout(p->cmd.name);
			ternary = (p->h.o[4]) ? ft_printf("(\"%s\")= ", p->r.msg)
				: ft_printf("(%s)= ", p->in_file);
			ft_puthex(hash->h, p->cmd.hash_hex_len, false, true);
		}
		else
		{
			ft_puthex(hash->h, p->cmd.hash_hex_len, false, false);
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
		ft_puthex(hash->h, p->cmd.hash_hex_len, false, true);
	}
	p->i[2]++;
	p->h.o[0] = (p->in_file) ? 1 : 0;
}
