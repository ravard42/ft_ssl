/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:59:27 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 14:59:28 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			str_parser(char *arg, t_parse *p)
{
	if (arg == NULL
		&& ft_dprintf(2, "%serror in str_parser: NULL arg%s\n", KRED, KNRM))
		return (0);
	p->r.len = ft_strlen(arg);
	if (!(p->r.msg = (char *)ft_memalloc(sizeof(char) * (p->r.len + 1))))
		return (-2);
	ft_memcpy(p->r.msg, arg, p->r.len);
	return (1);
}

int			fd_parser(char *arg, t_parse *p)
{
	int				tmp;

	if (p->o[1] && p->i[1] && !(p->o[1] = 0))
		return (1);
	if ((tmp = ft_read(arg, &(p->r))) < 0)
		return (tmp);
	if (arg)
		p->in_file = ft_strdup(arg);
	p->i[1] = (p->o[1]) ? 1 : p->i[1];
	return (1);
}
