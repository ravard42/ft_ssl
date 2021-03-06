/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:59:42 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 23:06:56 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void				init_h(t_hash *h, bool init)
{
	int8_t	i;

	if (!init)
		return ;
	i = -1;
	while (++i < 5)
		h->o[i] = 0;
	h->pbkdf = false;
}

static void				init_s(t_sym *s, bool init)
{
	int8_t		i;
	uint16_t	tmp;

	if (!init)
		return ;
	i = -1;
	while (++i < 9)
		s->o[i] = 0;
	i = -1;
	while (++i < 4)
	{
		s->arg[i].set = false;
		s->arg[i].p = NULL;
	}
	s->id_k = 0;
	tmp = 1;
	s->endian = (*((uint8_t *)&tmp)) ? 0 : 1;
}

static void				init_a(t_asym *a, bool init)
{
	int8_t	i;

	if (!init)
		return ;
	i = -1;
	while (++i < 13)
		a->o[i] = 0;
	a->mod_nb = 64;
	a->rsak = NULL;
	a->data.msg = NULL;
	a->data.len = -1;
}

static void				init_rng(t_rng *rng, bool init)
{
	if (!init)
		return ;
	if ((rng->fd = open("/dev/urandom", O_RDONLY)) == -1
		&& ft_dprintf(2, g_ssl_str[PRNG_ERR_OPEN_DEVURAND], KRED, KNRM))
		exit(0);
	rng->co = 0xa00000;
	init_s(&rng->s, init);
}

/*
**	init_opt			init
**		1		->		p (i, r, in_file, w, out_file)
**		2		->		h
**		4		->		s
**		8		->		a
**		16		->		rng
**	NB: combinable
**		 exempli gratia/e.g:
**		 init_opt == 15 (01111)
**		 will init  p(i, r, in_file, w, out_file)
**					 + h
**					 + s
**					 + a
*/

bool					init_p(t_parse *p, char *cmd, uint8_t init_opt)
{
	if (cmd && !cmd_parser(p, cmd))
		return (false);
	if (init_opt & 1)
	{
		p->i[0] = 1;
		p->i[1] = 0;
		p->i[2] = 0;
		p->in_file = NULL;
		p->r.msg = NULL;
		p->r.len = -1;
		p->out_file = NULL;
		p->w.fd = -1;
		p->w.msg = NULL;
		p->w.len = -1;
	}
	init_h(&p->h, init_opt & 2);
	init_s(&p->s, init_opt & 4);
	init_a(&p->a, init_opt & 8);
	init_rng(&p->rng, init_opt & 16);
	return (true);
}
