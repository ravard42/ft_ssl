/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:11:56 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 11:36:39 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					set_pass(t_parse *p, int verify)
{
	char	*tmp;

	tmp = getpass("enter password:");
	if (!ft_strlen(tmp) && ft_dprintf(2, "%sempty password%s\n", KRED, KNRM))
		return (0);
	p->s.arg[3].p = ft_strdup(tmp);
	p->s.arg[3].set = true;
	if (verify)
	{
		tmp = getpass("verify password:");
		if (ft_strcmp(p->s.arg[3].p, tmp)
				&& ft_dprintf(2, "%sverify failure%s\n", KRED, KNRM))
			return (0);
	}
	return (1);
}

static int			set_pass_salt(t_parse *p)
{
	if (!(p->s.arg[3].p) && !set_pass(p, 1))
		return (0);
	p->w.fd = -1;
	if (!p->s.arg[2].set)
	{
		p->w.fd = open("/dev/urandom", O_RDONLY);
		if (read(p->w.fd, &p->s.arg[2].x, 8) == -1
			&& ft_dprintf(2, "%sread error in pbkdf%s\n", KRED, KNRM))
			return (0);
		p->s.arg[2].set = true;
	}
	return (1);
}

/*
**int		sha256_pass_salt_hash(t_parse *tmp, t_parse *p)
**{
**	init_parse_struct(tmp);
**	tmp->h.pbkdf = true;
**	cmd_parser("sha256", tmp);
**	tmp->r.len = ft_strlen(p->s.arg[3].p) + 8;
**	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
**	ft_memcpy(tmp->r.msg, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
**	ft_memcpy(tmp->r.msg + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
**	if (!tmp->cmd.run(tmp))
**		return (0);
**	return (1);
**}
*/

static int			next_kdf_round(t_parse *tmp, uint32_t *h_tmp, t_parse *p)
{
	init_parse_struct(tmp);
	tmp->h.pbkdf = true;
	cmd_parser("md5", tmp);
	tmp->r.len = 16 + ft_strlen(p->s.arg[3].p) + 8;
	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
	ft_memcpy(tmp->r.msg, h_tmp, 16);
	ft_memcpy(tmp->r.msg + 16, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
	ft_memcpy(tmp->r.msg + 16 + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
	if (!tmp->cmd.run(tmp))
		return (0);
	return (1);
}

int					md5_pass_salt_hash(t_parse *tmp, t_parse *p)
{
	uint32_t	h_tmp[4];

	init_parse_struct(tmp);
	tmp->h.pbkdf = true;
	cmd_parser("md5", tmp);
	tmp->r.len = ft_strlen(p->s.arg[3].p) + 8;
	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
	ft_memcpy(tmp->r.msg, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
	ft_memcpy(tmp->r.msg + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
	if (!tmp->cmd.run(tmp))
		return (0);
	if (p->cmd.nb_k == 1)
		return (1);
	ft_memcpy(h_tmp, tmp->h.h, 16);
	if (!next_kdf_round(tmp, h_tmp, p))
		return (0);
	ft_memcpy(tmp->h.h + 4, tmp->h.h, 16);
	ft_memcpy(tmp->h.h, h_tmp, 16);
	return (1);
}

int					pbkdf(t_parse *p)
{
	t_parse		tmp;

	if (!set_pass_salt(p))
		return (0);
	if (!md5_pass_salt_hash(&tmp, p))
		return (0);
	ft_memcpy(p->s.arg[0].x, &tmp.h.h, 8 * p->cmd.nb_k);
	format_key(p);
	ft_memcpy(p->s.arg[1].x,
		(uint8_t *)&tmp.h.h + 8 * p->cmd.nb_k, 8);
	p->s.arg[0].set = true;
	p->s.arg[1].set = true;
	if (p->w.fd != -1)
		close(p->w.fd);
	return (1);
}
