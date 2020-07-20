/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:49:23 by ravard            #+#    #+#             */
/*   Updated: 2020/05/15 19:52:41 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool			rsa_pad(t_varint *data, t_parse *p, int nb_v)
{
	t_varint		*modulus;
	int16_t			diff_len;

	modulus = p->a.rsak + nb_v % 2;
	diff_len = modulus->len - p->a.data.len;
	if (diff_len < 11
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_2], KRED, KNRM))
		return (false);
	*data = g_v[0];
	data->x[1] = 0x02;
	if (!prng(data->x + 2, diff_len - 3, &p->rng, 1))
		return (false);
	data->x[diff_len - 1] = 0x00;
	ft_memcpy(data->x + diff_len, p->a.data.msg, p->a.data.len);
	data->len = modulus->len;
	return (true);
}

static bool			rsa_enc(t_varint *data, t_parse *p, int nb_v)
{
	if (p->a.o[7] && (data->len = p->a.data.len))
		ft_memcpy(data->x, p->a.data.msg, p->a.data.len);
	else if (!rsa_pad(data, p, nb_v))
		return (false);
	if (data->len < p->a.rsak[nb_v % 2].len
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_1], KRED, KNRM))
		return (false);
	if (data->len > p->a.rsak[nb_v % 2].len
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_2], KRED, KNRM))
		return (false);
	ft_memrev(data->x, data->len);
	v_len(data, data->len);
	if (v_cmp(data, "-ge", p->a.rsak + nb_v % 2, false)
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_3], KRED, KNRM))
		return (false);
	*data = v_expmod(*data, p->a.rsak[1 + nb_v % 2], p->a.rsak[nb_v % 2], true);
	if (is_g_v(3, data))
		return (false);
	ft_memrev(data->x, data->len);
	ft_memshift(data->x, data->len, p->a.rsak[nb_v % 2].len - data->len);
	ft_memset((char *)data->x, 0, p->a.rsak[nb_v % 2].len - data->len);
	data->len = p->a.rsak[nb_v % 2].len;
	return (true);
}

static bool			rsa_unpad(t_varint *data)
{
	int16_t	i;

	if (data->x[0] != 0x02
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_UNPAD_0], KRED, KNRM))
		return (false);
	i = -1;
	while (++i < data->len && data->x[i] != 0x00)
		;
	if ((i == data->len || i < 9)
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_UNPAD_1], KRED, KNRM))
		return (false);
	ft_memshift(data->x + i + 1, data->len - (i + 1), 0 - (i + 1));
	data->len = data->len - (i + 1);
	return (true);
}

static bool			rsa_dec(t_varint *data, t_parse *p, int nb_v)
{
	if (nb_v != 9 && ft_dprintf(2, g_ssl_str[RSAU_ERR_KEY], KRED, KNRM))
		return (false);
	ft_memrcpy(data->x, p->a.data.msg, p->a.data.len);
	v_len(data, p->a.data.len);
	if (v_cmp(data, "-ge", p->a.rsak + 1, false) &&
		ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_3], KRED, KNRM))
		return (false);
	*data = cra(data, p->a.rsak);
	if (is_g_v(3, data))
		return (false);
	ft_memrev(data->x, data->len);
	if (p->a.o[7])
	{
		ft_memshift(data->x, data->len, p->a.rsak[1].len - data->len);
		ft_memset((char *)data->x, 0, p->a.rsak[1].len - data->len);
		data->len = p->a.rsak[1].len;
	}
	else if (!rsa_unpad(data))
		return (false);
	return (true);
}

/*
**	RSAUTL OPTS
**
**	o[3] : 1 for -pubin, else 0
**	o[4] : 1 for -encrypt, else 0
**	o[5] : 1 for -decrypt, else 0
**	o[6] : 1 for -hexdump, else 0
**	o[7] : 1 for -raw, else 0
**
**	NB: we copy all asym options p->a.o[] in tmp_o before we call read_rsak
**	endeed read_rsak react to p->a.o[], so we need to clear it!
**	-pubin is the only key option we have to handle here.
**	(always PEM keys and never des encrypted)
*/

int					rsautl(t_parse *p)
{
	int			nb_v;
	uint8_t		tmp_o[13];
	t_varint	data;

	ft_memcpy(&tmp_o, p->a.o, 13);
	ft_memset((char *)p->a.o, 0, 13);
	p->a.o[7] = tmp_o[3];
	if (!(nb_v = read_rsak(p)))
		return (-1);
	ft_memcpy(p->a.o, &tmp_o, 13);
	data = g_v[0];
	if (p->a.o[4] && !rsa_enc(&data, p, nb_v))
		return (-1);
	if (p->a.o[5] && !rsa_dec(&data, p, nb_v))
		return (-1);
	p->w.fd = (p->out_file) ?
		open(p->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644) : 1;
	if (p->w.fd == -1 && ft_dprintf(2, g_ssl_str[RSAU_ERR_OUT_FD], KRED, KNRM))
		return (-1);
	if (p->a.o[6])
		ft_hexdump(p->w.fd, (char *)data.x, data.len);
	else
		nb_v = write(p->w.fd, data.x, data.len);
	return (0);
}
