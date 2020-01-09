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

static void				init_asym_p(t_parse *p)
{
	(void)p;
	ft_dprintf(2, "%sto be computed%s", KCYN, KNRM);
}

static void				init_hash_p(t_parse *p)
{
	int8_t	i;

	i = -1;
	while (++i < 5)
		p->h.o[i] = 0;
	p->h.pbkdf = false;
}

static void				init_sym_p(t_parse *p)
{
	int8_t	i;

	i = -1;
	while (++i < 9)
		p->s.o[i] = 0;
	i = -1;
	while (++i < 4)
		p->s.arg[i].set = false;
	p->s.arg[3].p = NULL;
	p->s.id_k = 0;
}

int				init_p(t_parse *p, char *cmd)
{
	if (!cmd_parser(p, cmd))
		return (0);
	p->i[0] = 1;
	p->i[1] = 0;
	p->i[2] = 0;
	p->r.msg = NULL;
	p->r.len = 0;
	p->in_file = NULL;
	p->w.fd = -1;
	p->w.msg = NULL;
	p->w.len = 0;
	p->out_file = NULL;
	if (p->cmd.type == 0)
		init_asym_p(p);
	else if (p->cmd.type == 1)
		init_hash_p(p);
	else if (p->cmd.type == 2)
		init_sym_p(p);
	return (1);
}


// need to be improved -> free_p(t_parse *p)
void				free_parse_struct(t_parse *p)
{
	p->h.o[1] = 0;
	p->h.o[4] = 0;

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
	//particularly here ??
	if (p->cmd.type == 2 && p->s.arg[3].p)
		free(p->s.arg[3].p);
	//
	p->s.arg[3].p = NULL;
}
