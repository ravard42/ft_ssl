/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_des_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:19:49 by ravard            #+#    #+#             */
/*   Updated: 2020/05/15 19:19:52 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** used in read_rsak
*/

/*
** check_enc_header
**
**	read encryption header if one and set p->a.iv_salt,
** offset[0] must point on b64 data at the end of this function
**
**	return 1 if ok, 0 if error
*/

int						check_enc_header(int64_t *offset, t_parse *p)
{
	if ((offset[1] = ft_grep_line(g_rsa_header[4],
					&p->r, offset[0])) == offset[0])
	{
		offset[0] += ft_strlen(g_rsa_header[4]);
		if (p->r.len - offset[0] <= 16
			&& ft_dprintf(2, "%sincomplete header%s\n", KRED, KNRM))
			return (0);
		if (!hstr_to_64_t(p->s.arg[2].x, 1, p->r.msg + offset[0], false)
			&& ft_dprintf(2, "%serror reading initial vector%s\n", KRED, KNRM))
			return (0);
		p->s.arg[2].set = true;
		if ((offset[0] = ft_nxt_line(&p->r, offset[0])) <= 0)
			return (0);
	}
	offset[0] += p->r.msg[offset[0]] == '\n' ? 1 : 0;
	return (1);
}

int						pem_des_dec(t_parse *p)
{
	t_parse		tmp;

	if (!p->s.arg[0].p && !(p->s.arg[0].p = set_pass(false)))
		return (0);
	p->s.arg[3].p = p->s.arg[0].p;
	if (!md5_pbkdf(&tmp, p))
		return (0);
	p->s.arg[3].p = NULL;
	ft_memcpy(p->s.arg[0].x, &tmp.h.h, 8);
	p->s.arg[0].set = true;
	format_key(&p->s, 1);
	p->s.arg[1].x[0] = p->s.arg[2].x[0];
	p->s.arg[1].set = true;
	if (!opt_a_d(p))
		return (0);
	if (!des_dec(p))
		return (0);
	free(p->r.msg);
	p->r.msg = p->w.msg;
	p->w.msg = NULL;
	p->r.len = p->w.len;
	return (1);
}

/*
**	used in write_rsak
*/

static int				des_pbkdf(t_parse *p)
{
	t_parse tmp;

	if (!prng(p->s.arg[2].x, 8, &p->rng, 0))
		return (0);
	p->s.arg[2].set = true;
	p->s.arg[3].p = p->s.arg[1].p;
	if (!md5_pbkdf(&tmp, p))
		return (0);
	p->s.arg[3].p = NULL;
	ft_memcpy(p->s.arg[0].x, &tmp.h.h, 8);
	p->s.arg[0].set = true;
	format_key(&p->s, 1);
	p->s.arg[1].x[0] = p->s.arg[2].x[0];
	p->s.arg[1].set = true;
	p->s.arg[2].set = false;
	return (1);
}

int						des_enc_b64(t_parse *p, int nb_v)
{
	if (nb_v != 9 && ft_dprintf(2, g_ssl_str[RSA_ERR_DES], KRED, KNRM))
	{
		p->a.o[6] = 0;
		return (1);
	}
	if (!des_pbkdf(p))
		return (0);
	if (!des_enc(p))
		return (0);
	if (!opt_a_e(p))
		return (0);
	return (1);
}
