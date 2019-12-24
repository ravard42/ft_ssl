/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:59:42 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:01:13 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			init_sub_struct(t_parse *p)
{
	int	i;

	ft_memset(p->cmd.name, 0, 10);
	p->cmd.endian = 0;
	p->cmd.hash_hex_len = 0;
	p->cmd.needed[0] = false;
	p->cmd.needed[1] = false;
	p->cmd.run = NULL;
	p->h.pbkdf = false;
	i = -1;
	while (++i < 4)
		p->s.arg[i].set = false;
	p->s.arg[3].p = NULL;
	p->s.id_k = 0;
}

void				init_parse_struct(t_parse *p)
{
	int8_t	i;

	p->i[0] = 1;
	p->i[1] = 0;
	p->i[2] = 0;
	i = -1;
	while (++i < 14)
		p->o[i] = 0;
	p->in_file = NULL;
	p->out_file = NULL;
	p->r.msg = NULL;
	p->r.len = 0;
	p->w.msg = NULL;
	p->w.len = 0;
	init_sub_struct(p);
}

void				free_parse_struct(t_parse *p)
{
	p->o[1] = 0;
	p->o[4] = 0;
	if (p->in_file)
		free(p->in_file);
	p->in_file = NULL;
	if (p->out_file)
		free(p->out_file);
	p->out_file = NULL;
	if (p->r.msg)
		free(p->r.msg);
	p->r.msg = NULL;
	p->r.len = 0;
	if (p->w.msg)
		free(p->w.msg);
	p->w.msg = NULL;
	p->w.len = 0;
	if (p->s.arg[3].p)
		free(p->s.arg[3].p);
	p->s.arg[3].p = NULL;
}
