/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:03:16 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:03:45 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	tmp = -2 => fatal error (cmd not valide / allocation error) -> exit
**	tmp = -1 => parsing error (open, read, opt non valide) -> handle next arg
**	tmp = 0 => no more arg to be compute -> exit
**	tmp = 1 => all is OK -> hash it
*/

int	main(int argc, char **argv)
{
	t_parse			p;
	int				tmp;

	init_parse_struct(&p);
	if (argc == 1 || !cmd_parser(argv[1], &p))
		return (usage());
	while ((tmp = p.cmd.parser(argc, argv, &p)))
	{
		if (tmp == -2)
			break ;
		else if (tmp == -1)
			continue;
		if (!p.cmd.run(&p))
			break ;
	}
	free_parse_struct(&p);
	return (0);
}
