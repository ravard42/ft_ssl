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
**	main return status:
**	0 : all works fine
**	1 : init fatal error (bad cmd)
**	2 : parsing error (hash only)
**	3 : parsing fatal error 
**	4 : cmd fatal error
*/

/*
**	parser return status:
**	-2 : fatal error 	-> exit
**	-1 : error 			-> handle next arg (hash func only)
**	0 	: no more arg	->	exit
**	1 	: arg loaded 	-> run cmd
*/

/*
**	cmd return status:
**	-1 : fatal error 	-> exit
**	0 	: cmd success	->	exit
**	1 	: cmd sucess 	-> parser
*/

int	main(int argc, char **argv)
{
	t_parse			p;
	int				p_ret;
	int				c_ret;
	int				ret;

	if (argc == 1 || !init_p(&p, argv[1], 31))
		return (cmd_usage());
	ret = 0;
	while ((p_ret = p.cmd.parser(&p, argc, argv)))
	{
		if (p_ret == -2 && (ret = 3))
			break ;
		else if (p_ret == -1 && (ret = 2))
			continue;
		c_ret = p.cmd.run(&p);
		if ((c_ret == -1 && (ret = 4)) || c_ret == 0)
			break ;
	}
	free_p(&p, 31);
	return (ret);
}
