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

static void		handle_s_p_opts(t_parse *p, t_hash *hash)
{
	char	ternary;

	(void)ternary;
	if (p->o[2])
		print_hexa(hash->h, p->cmd.hash_hex_len, true);
	else
	{
		if (!p->o[3])
		{
			toupper_stdout(p->cmd.name);
			ternary = (p->o[4]) ? ft_printf(" (\"%s\") = ", p->r.msg)
				: ft_printf(" (%s) = ", p->in_file);
			print_hexa(hash->h, p->cmd.hash_hex_len, true);
		}
		else
		{
			print_hexa(hash->h, p->cmd.hash_hex_len, false);
			ternary = (p->o[4]) ? ft_printf(" \"%s\"\n", p->r.msg)
				: ft_printf(" %s\n", p->in_file);
		}
	}
}

void			print_format(t_parse *p, t_hash *hash)
{
	if (p->o[4] || p->in_file)
		handle_s_p_opts(p, hash);
	else
	{
		if (p->o[1])
			ft_printf("%s", p->r.msg);
		print_hexa(hash->h, p->cmd.hash_hex_len, true);
	}
	p->i[2]++;
	p->o[0] = (p->in_file) ? 1 : 0;
}
