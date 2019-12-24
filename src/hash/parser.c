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

int			hash_parser(int argc, char **argv, t_parse *p)
{
	if (p->i[0] == argc && p->i[2] != 0)
		return (0);
	p->i[0]++;
	while (!p->o[0] && argv[p->i[0]] && argv[p->i[0]][0] == '-')
	{
		if (!opt_parser(argv[p->i[0]], p))
			return (usage());
		if ((p->o[4] && ++(p->i[0])))
			return (str_parser(argv[p->i[0]], p));
		if (p->o[1])
			return (fd_parser(NULL, p));
		p->i[0]++;
	}
	if (p->i[2] == 0 && !argv[p->i[0]])
		return (fd_parser(NULL, p));
	if (argv[p->i[0]])
		return (fd_parser(argv[p->i[0]], p));
	return (0);
}
