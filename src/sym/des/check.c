/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:35:03 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 13:54:37 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			check_out(t_parse *p)
{
	p->w.fd = (p->out_file) ?
		open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644) : 1;
	if (p->w.fd == -1
		&& ft_dprintf(2, "%sout_file opening error\n%s", KRED, KNRM))
		return (0);
	return (1);
}

int			check_k_v(t_parse *p)
{
	p->i[1] = p->s.o[1] && p->r.msg
		&& !ft_strncmp(p->r.msg, "Salted__", 8) ? 2 : 0;
	if (!p->i[1])
	{
		if (p->s.arg[0].set
			&& (p->s.arg[1].set || !p->cmd.needed[1]))
			return (1);
		ft_dprintf(2, g_ssl_str[DES_ERR_KVS], KRED, KNRM);
		return (0);
	}
	if (!pbkdf(p, false, p->r.msg + 8))
		return (0);
	return (1);
}
