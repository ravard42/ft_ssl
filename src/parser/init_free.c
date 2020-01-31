/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:59:42 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 03:26:38 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void				init_asym_p(t_asym *a)
{
	int8_t	i;

	i = -1;
	while (++i < 2)
		a->o[i] = 0;
	a->mod_nb = 128;
}

static void				init_hash_p(t_hash *h)
{
	int8_t	i;

	i = -1;
	while (++i < 5)
		h->o[i] = 0;
	h->pbkdf = false;
}

static void				init_sym_p(t_sym *s)
{
	int8_t	i;

	i = -1;
	while (++i < 9)
		s->o[i] = 0;
	i = -1;
	while (++i < 4)
		s->arg[i].set = false;
	s->arg[3].p = NULL;
	s->id_k = 0;
	s->endian = 1;
	s->endian = (*(uint8_t *)&s->endian) ? 0 : 1;
}

int						init_p(t_parse *p, char *cmd)
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
		init_asym_p(&p->a);
	else if (p->cmd.type == 1)
		init_hash_p(&p->h);
	else if (p->cmd.type == 2)
		init_sym_p(&p->s);
	p->rng.fd = -1;
	p->rng.co = 0xa00000;
	init_sym_p(&p->rng.s);
	return (1);
}

void					free_p(t_parse *p)
{
	if (p->r.msg)
		free(p->r.msg);
	p->r.msg = NULL;
	p->r.len = 0;
	if (p->in_file)
		free(p->in_file);
	p->in_file = NULL;
	if (p->w.fd > 1)
		close(p->w.fd);
	p->w.fd = -1;
	if (p->w.msg)
		free(p->w.msg);
	p->w.msg = NULL;
	p->w.len = 0;
	if (p->out_file)
		free(p->out_file);
	p->out_file = NULL;
	p->h.o[1] = 0;
	p->h.o[4] = 0;
	if (p->cmd.type == 2 && p->s.arg[3].p)
		free(p->s.arg[3].p);
	p->s.arg[3].p = NULL;
}
