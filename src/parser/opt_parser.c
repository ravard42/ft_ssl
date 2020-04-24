/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:01:24 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 07:09:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

bool				opt_parser(t_parse *p, const char **opts, char *arg)
{
	int8_t			i;
	int8_t			j;

	j = -1;
	i = -1;
	while (ft_strcmp(opts[++i], "")
		&& (j = ft_strcmp(opts[i], arg)))
		;
	if (j == 0)
	{
		if (p->cmd.type == 0)
			return (p->a.o[i] = 1);
		else if (p->cmd.type == 1)
			return (p->h.o[i + 1] = 1);
		else if (p->cmd.type == 2)
			return (p->s.o[i] = 1);
	}
	ft_dprintf(2, "%s\"%s\" invalid option%s\n", KRED, arg, KNRM);
	return (false);
}

int				opt_usage(char *title, const char **usg)
{
	int	i;

	i = -1;
	ft_dprintf(2, "%s%s%s:\n", KYEL, title, KNRM);
	while (ft_strcmp(usg[++i], ""))
		ft_dprintf(2, " %s\n", usg[i]);
	return (-2);
}
