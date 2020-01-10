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

static const char		*g_hash_usg[] = {P, Q, R, S, ""};
static const char		*g_hash_opt[] = {"-p", "-q", "-r", "-s", ""};

int			hash_parser(t_parse * p, int argc, char **argv)
{
	if (p->i[0] == argc && p->i[2] != 0)
		return (0);
	p->i[0]++;
	while (!p->h.o[0] && argv[p->i[0]] && argv[p->i[0]][0] == '-')
	{
		if (!opt_parser(p, g_hash_opt, argv[p->i[0]]))
			return (opt_usage("Message Digest opts", g_hash_usg));
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
