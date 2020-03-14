/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:11:56 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:37:59 by ravard           ###   ########.fr       */
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

static int			set_salt(t_parse *p, char *salt)
{
	int fd;

	if (salt)
	{
		if (p->r.len < 16)
			return (0);
		ft_memcpy(p->s.arg[2].x, salt, 8);
	}
	else
	{
		if ((fd = open("/dev/urandom", O_RDONLY)) == -1
			&& ft_dprintf(2, "%sopen /dev/urandom error in pbkdf%s\n", KRED, KNRM))
			return (0);
		if (read(fd, &p->s.arg[2].x, 8) == -1
			&& ft_dprintf(2, "%sread error in pbkdf%s\n", KRED, KNRM))
			return (0);
	}
	p->s.arg[2].set = true;
	return (1);
}

int					pbkdf(t_parse *p, bool verify, char *salt)
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
