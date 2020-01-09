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
**	tmp = -2 => malloc error -> exit
**	tmp = -1 => parsing error (open, read, opt non valide) -> handle next arg
**	tmp = 0 => no more arg to be computed -> exit
**	tmp = 1 => all is OK -> run cmd
*/

int	main(int argc, char **argv)
{
	t_parse			p;
	int				tmp;

	if (argc == 1 || !init_p(&p, argv[1]))
		return (cmd_usage());
	while ((tmp = p.cmd.parser(&p, argc, argv)))
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
