/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 11:35:03 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 11:35:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			check_out(t_parse *p)
{
	if (p->out_file)
		p->w.fd = open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		p->w.fd = 1;
	if (p->w.fd == -1 && ft_dprintf(2, "%sout_file opening error\n%s", KRED, KNRM))
		return (0);
	return (1);
}

int			check_k_v(t_parse *p)
{
	t_parse		tmp;

	p->i[1] = p->o[6] && !ft_strncmp(p->r.msg, "Salted__", 8) ? 2 : 0;
	if (!p->i[1] && p->s.arg[0].set
		&& (!p->cmd.needed[1] || p->s.arg[1].set))
		return (1);
	if (!p->i[1] && (!p->s.arg[0].set
			|| (p->cmd.needed[1] && !p->s.arg[1].set))
		&& ft_dprintf(2, "%sk and/or v undefined and salt missing%s\n", KRED, KNRM))
		return (0);
	if (!(p->s.arg[3].set) && !set_pass(p, 0))
		return (0);
	ft_memcpy(p->s.arg[2].x, p->r.msg + 8, 8);
	md5_pass_salt_hash(&tmp, p);
	ft_memcpy(p->s.arg[0].x, &tmp.h.h, 8 * p->cmd.nb_k);
	format_key(p);
	ft_memcpy(p->s.arg[1].x,
		(uint8_t *)&tmp.h.h + 8 * p->cmd.nb_k, 8);
	p->s.arg[0].set = true;
	p->s.arg[1].set = true;
	return (1);
}
