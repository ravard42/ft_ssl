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

int					set_pass(t_parse *p, bool verify)
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
		if ((fd = open("/dev/urandom", O_RDONLY) == -1)
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

	if (!(p->s.arg[3].p) && !set_pass(p, verify))
		return (0);
	if (!(p->s.arg[2].set) && !set_salt(p, salt))
		return (0);
	if (!EVP_BYTES_TO_KEY(&tmp, p))
		return (0);
	ft_memcpy(p->s.arg[0].x,
		&tmp.h.h, 8 * p->cmd.nb_k);
	format_key(p);
	ft_memcpy(p->s.arg[1].x,
		(uint8_t *)&tmp.h.h + 8 * p->cmd.nb_k, 8);
	p->s.arg[0].set = true;
	p->s.arg[1].set = true;
	return (1);
}
