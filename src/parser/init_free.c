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

static bool				init_sym_p(t_sym *s)
{
	int8_t	i;
	uint16_t	tmp;

	i = -1;
	while (++i < 9)
		s->o[i] = 0;
	i = -1;
	while (++i < 4)
		s->arg[i].set = false;
	s->arg[3].p = NULL;
	s->id_k = 0;
	tmp = 1;
	s->endian = (*((uint8_t *)&tmp)) ? 0 : 1;
	return (true);
}

static bool				init_asym_p(t_parse *p)
{
	int8_t	i;

	//we are gonna use b64 and des in there
	init_sym_p(&p->s);
	i = -1;
	while (++i < 13)
		p->a.o[i] = 0;
	p->a.pi = NULL;
	p->a.po = NULL;
	if (!ft_strcmp("genrsa", p->cmd.name))
	{
		p->a.mod_nb = 64;
		if ((V_MAX_LEN < 8 || V_MAX_LEN > 512)
			&& ft_dprintf(2, "%s%s%s", KRED, V_GENRSA_STACK_ERR, KNRM))
		return (false);
		if (!(p->a.rsak = (t_varint *)ft_memalloc(sizeof(t_varint) * 9))
			&& ft_dprintf(2, "%srsak malloc error%s\n", KRED, KNRM))
			return (false);
	}
	else
		p->a.rsak = NULL;
	return (true);
}

static bool				init_hash_p(t_hash *h)
{
	int8_t	i;

	i = -1;
	while (++i < 5)
		h->o[i] = 0;
	h->pbkdf = false;
	return (true);
}


int						init_p(t_parse *p, char *cmd)
{
	if (!cmd_parser(p, cmd))
		return (-1);
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
	if (p->cmd.type == 0 && !init_asym_p(p))
		return (0);
	else if (p->cmd.type == 1 && !init_hash_p(&p->h))
		return (0);
	else if (p->cmd.type == 2 && !init_sym_p(&p->s))
		return (0);
	p->rng.fd = -1;
	p->rng.co = 0xa00000;
	init_sym_p(&p->rng.s);
	return (1);
}

void					free_p(t_parse *p)
{
	if (p->rng.fd > 1)
		close(p->rng.fd);
	p->rng.fd = -1;
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
	if (p->cmd.type == 0 && p->a.pi)
		free(p->a.pi);
	p->a.pi = NULL;
	if (p->cmd.type == 0 && p->a.po)
		free(p->a.po);
	p->a.po = NULL;
	if (p->cmd.type == 0 && p->a.rsak)
		free(p->a.rsak);
	p->a.rsak = NULL;
}
