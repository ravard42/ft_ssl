/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:17:10 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 20:19:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			hash_parser(t_parse * p, int argc, char **argv)
{
	if (p->i[0] == argc && p->i[2] != 0)
		return (0);
	p->i[0]++;
	while (!p->h.o[0] && argv[p->i[0]] && argv[p->i[0]][0] == '-')
	{
		if (!hash_opt(p, argv[p->i[0]]))
			return (hash_opt_usage());
		if ((p->h.o[4] && ++(p->i[0])))
			return (str_parser(p, argv[p->i[0]]));
		if (p->h.o[1])
			return (fd_parser(p, NULL));
		p->i[0]++;
	}
	if (p->i[2] == 0 && !argv[p->i[0]])
		return (fd_parser(p, NULL));
	if (argv[p->i[0]])
		return (fd_parser(p, argv[p->i[0]]));
	return (0);
}
