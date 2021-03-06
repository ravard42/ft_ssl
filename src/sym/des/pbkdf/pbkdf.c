/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:11:56 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 13:57:41 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char					*set_pass(bool verify)
{
	char	*tmp;
	char	*pw;

	tmp = getpass("enter password:");
	if (ft_strlen(tmp) < 4
		&& ft_dprintf(2, "%spassword need at least 4 char%s\n", KRED, KNRM))
		return (NULL);
	if (!(pw = ft_strdup(tmp)))
		return (NULL);
	if (verify)
	{
		tmp = getpass("verify password:");
		if (ft_strcmp(pw, tmp))
		{
			ft_dprintf(2, "%sverify failure%s\n", KRED, KNRM);
			free(pw);
			return (NULL);
		}
	}
	return (pw);
}

static int				set_salt(t_parse *p, char *salt)
{
	if (salt)
	{
		if (p->r.len < 16)
			return (0);
		ft_memcpy(p->s.arg[2].x, salt, 8);
	}
	else if (!prng(p->s.arg[2].x, 8, &p->rng, 0))
		return (0);
	p->s.arg[2].set = true;
	return (1);
}

int						pbkdf(t_parse *p, bool verify, char *salt)
{
	t_parse		tmp;

	if (!(p->s.arg[3].p) && !(p->s.arg[3].p = set_pass(verify)))
		return (0);
	p->s.arg[3].set = true;
	if (!(p->s.arg[2].set) && !set_salt(p, salt))
		return (0);
	if (!EVP_BYTES_TO_KEY(&tmp, p))
		return (0);
	ft_memcpy(p->s.arg[0].x,
		&tmp.h.h, 8 * p->cmd.nb_k);
	format_key(&p->s, p->cmd.nb_k);
	ft_memcpy(p->s.arg[1].x,
		(uint8_t *)&tmp.h.h + 8 * p->cmd.nb_k, 8);
	p->s.arg[0].set = true;
	p->s.arg[1].set = true;
	return (1);
}
