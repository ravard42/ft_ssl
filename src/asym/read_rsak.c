/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rsak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:54:59 by ravard            #+#    #+#             */
/*   Updated: 2020/05/15 19:19:11 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const char			*g_rsa_header[] = {
	"-----BEGIN RSA PRIVATE KEY-----\n",
	"-----BEGIN PUBLIC KEY-----\n",
	"-----END RSA PRIVATE KEY-----\n",
	"-----END PUBLIC KEY-----\n",
	"Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC,"
};

/*
** grep_pem
**
** scan t_read *r to find a pem valid sequence.
*/

int					grep_pem(t_parse *p)
{
	int64_t	offset[2];

	offset[0] = 0;
	if ((offset[0] = ft_grep_line(g_rsa_header[p->a.o[7]],
					&p->r, offset[0])) < 0)
		return (0);
	if ((offset[0] = ft_nxt_line(&p->r, offset[0])) <= 0)
		return (0);
	if (!p->a.o[7] && check_enc_header(offset, p) == -1)
		return (0);
	if ((offset[1] = ft_grep_line(g_rsa_header[2 + p->a.o[7]],
					&p->r, offset[0])) < 0)
		return (0);
	ft_memcpy(p->r.msg, p->r.msg + offset[0], offset[1] - offset[0]);
	p->r.msg[offset[1] - offset[0]] = 0;
	p->r.len = offset[1] - offset[0];
	return (1);
}

static int64_t		der_pub_offset(char *data, int64_t len)
{
	int64_t i;

	i = -1;
	while (++i < len - 1)
		if (data[i] == 0x00 && data[i + 1] == 0x30)
			return (i + 1);
	ft_dprintf(2, "%sder_pub_offset error%s\n", KRED, KNRM);
	return (-1);
}

int					pem_2_der(t_parse *p)
{
	int64_t	der_offset;

	if (!grep_pem(p)
		&& ft_dprintf(2, "%sInvalid PEM file%s\n", KRED, KNRM))
		return (0);
	if (!p->s.arg[2].set)
	{
		if (run_b64_d(p) == -2)
			return (0);
		der_offset = (p->a.o[7]) ? der_pub_offset(p->w.msg, p->w.len) : 0;
		if (der_offset == -1)
			return (0);
		ft_memcpy(p->r.msg, p->w.msg + der_offset, p->w.len - der_offset);
		p->r.len = (p->a.o[7]) ? p->w.len - der_offset : p->w.len;
		return (1);
	}
	return (pem_des_dec(p));
}

/*
**	About read_rsak
**
**	ASN1 DER DECODING prototype:
**	t_varint	*v_asn1_int_seq_der_d(int *nb_varint, t_read *r)
**
**	t_read *r must contain a valid DER interger sequence
**	nb_varint could be:
**	9 for private keys: version, n, e, d, p, q, dp, dq, qinv
**	2 for public keys : n, e
**
**	o[2] : -inform (0 for PEM, 2 for DER)
**	o[4] : 1 for -passin, else 0
**	o[7] : 1 for -pubin, else 0
*/

int					read_rsak(t_parse *p)
{
	int64_t	offset;
	int		nb_v;

	if (!p->a.o[2] && !pem_2_der(p))
		return (0);
	else if (p->a.o[2] && p->a.o[7])
	{
		offset = der_pub_offset(p->r.msg, p->r.len);
		ft_memcpy(p->r.msg, p->r.msg + offset, p->r.len - offset);
		p->r.len -= offset;
	}
	p->a.rsak = v_asn1_int_seq_der_d(&nb_v, &p->r);
	if ((!p->a.rsak || (nb_v != 2 && nb_v != 9))
		&& ft_dprintf(2, "%srsa key loading error%s\n", KRED, KNRM))
		return (0);
	free_if((void **)&p->r.msg);
	free_if((void **)&p->w.msg);
	return (nb_v);
}
