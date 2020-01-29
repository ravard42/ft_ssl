/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_asn1_der_int_seq_e.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:29 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 05:38:46 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		set_fd(char *out)
{
	int	fd;

	if (out == NULL)
		return (1);
	if ((fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1
		&& ft_dprintf(2, "%sopen error in asn1 der encoding%s\n", KRED, KNRM))
		return (-1);
	return (fd);
}

static int8_t	put_header(uint8_t *h, uint8_t type, unsigned int len)
{
	if (len > 0xffff
		&& ft_dprintf(2, "%s%s%s", KRED, V_DER_2_BIG, KNRM))
		return (-1);
	ft_memset((char *)h, 0, 5);
	h[1] = type;
	if (len < 0x80)
	{
		h[0] = 2;
		h[2] = len;
	}
	else if (len <= 0xff)
	{
		h[0] = 3;
		h[2] = 0x81;
		h[3] = len;
	}
	else if (len <= 0xffff)
	{
		h[0] = 4;
		h[2] = 0x82;
		h[3] = len >> 8;
		h[4] = len & 0xff;
	}
	return (0);
}

static int		set_sub_header(uint8_t *h, t_varint v)
{
	V_TYPE	mask;
	int8_t	k;
	int		val_len;
	int		tot_len;

	mask = 0xff;
	k = V_LEN - 1;
	while (k != 0
		&& !(v.x[v.len - 1] & (mask << 8 * k)))
		--k;
	val_len = v.len * V_LEN - (V_LEN - 1) + k;
	mask = 0x80;
	h[5] = (v.x[v.len - 1] & (mask << 8 * k)) ? 1 : 0;
	if (put_header(h, 0x02, h[5] + val_len) == -1)
		return (-1);
	tot_len = h[0] + h[5] + val_len;
	return (tot_len);
}

static void		put_value(int fd_out, t_varint *v)
{
	V_TYPE		mask;
	int8_t		k;
	V_LEN_TYPE	j;
	uint8_t		buff;

	mask = 0xff;
	k = V_LEN - 1;
	while (k != 0
		&& !(v->x[v->len - 1] & (mask << 8 * k)))
		k--;
	j = v->len;
	while (--j >= 0)
	{
		k = (j == v->len - 1) ? k : V_LEN - 1;
		while (k >= 0)
		{
			buff = v->x[j] >> 8 * k;
			write(fd_out, &buff, 1);
			k--;
		}
	}
}

/*
**	about h[1 + nb_varint][6]:
**	index 0 for sequence header, and others for integer headers
**	h[x][0] = header len
**	h[x][1:4] = header
**  h[x][5] = add sign byte (or not) between header and value
*/

int				v_asn1_der_int_seq_e(char *out, t_varint *v, int nb_varint)
{
	unsigned int	seq_len;
	int				i;
	int				tmp;
	uint8_t			h[1 + nb_varint][6];
	static uint8_t	sign_byte = 0x00;

	seq_len = 0;
	i = -1;
	while (++i < nb_varint
		&& (tmp = set_sub_header(h[i + 1], v[i])) != -1)
		seq_len += tmp;
	if (tmp == -1 || put_header(h[0], 0x30, seq_len) == -1)
		return (-1);
	if ((tmp = set_fd(out)) == -1)
		return (-1);
	write(tmp, h[0] + 1, h[0][0]);
	i = -1;
	while (++i < nb_varint)
	{
		write(tmp, h[i + 1] + 1, h[i + 1][0]);
		if (h[i + 1][5])
			write(tmp, &sign_byte, 1);
		put_value(tmp, v + i);
	}
	return (0);
}
