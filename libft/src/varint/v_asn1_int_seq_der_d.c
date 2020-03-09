/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_asn1_int_seq_der_d.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 05:39:11 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 05:47:43 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				free_der_d(t_der_d *o)
{
	t_der_d	*nxt;

	nxt = o->nxt;
	while (nxt)
	{
		o = nxt->nxt;
		free(nxt);
		nxt = o;
	}
	return (1);
}

static int				read_header(t_der_d *cu, int left)
{
	if (left < 3
		|| !((cu->st_h[0] == 0x30 && cu->id == -1) || cu->st_h[0] == 0x02))
		return (-1);
	if (cu->st_h[1] > 0 && cu->st_h[1] < 0x80
		&& (cu->st = cu->st_h + 2))
		cu->len = cu->st_h[1];
	else if (cu->st_h[1] == 0x81 && left >= 4 && cu->st_h[2] >= 0x80
		&& (cu->st = cu->st_h + 3))
		cu->len = cu->st_h[2];
	else if (cu->st_h[1] == 0x82 && left >= 5 && cu->st_h[2] >= 1
		&& (cu->st = cu->st_h + 4))
		cu->len = (cu->st_h[2] << 8) + cu->st_h[3];
	else
		return (-1);
	left -= (cu->id == -1) ? cu->st - cu->st_h : cu->st - cu->st_h + cu->len;
	if (left > 0)
	{
		if (!(cu->nxt = (t_der_d *)malloc(sizeof(t_der_d)))
			&& ft_dprintf(2, "%smalloc error: asn1%s\n", KRED, KNRM))
			return (-1);
		cu->nxt->id = cu->id + 1;
		cu->nxt->st_h = (cu->id == -1) ? cu->st : cu->st + cu->len;
		cu->nxt->nxt = NULL;
	}
	return (left);
}

static int				check_and_count(t_der_d *o, t_read *r)
{
	int		tmp;
	t_der_d	*cur;
	int		ret;

	tmp = r->len;
	cur = o;
	while (tmp)
	{
		tmp = read_header(cur, tmp);
		if (tmp < 0 && ft_dprintf(2, "%s%s%s", KRED, V_DER_COR, KNRM)
			&& free_der_d(o))
			return (-1);
		cur = cur->nxt;
	}
	cur = o;
	tmp = 0;
	ret = 0;
	while ((cur = cur->nxt) != NULL && ++ret)
		tmp += cur->st - cur->st_h + cur->len;
	if (tmp != (o->len) && ft_dprintf(2, "%s%s%s", KRED, V_DER_COR, KNRM)
		&& free_der_d(o))
		return (-1);
	return (ret);
}

static t_varint			v_load(uint8_t *src, int len)
{
	int			i;
	t_varint	ret;

	if (len > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_DER_OVFL, KNRM))
		return (g_v[3]);
	ret = g_v[0];
	i = len;
	while (--i >= 0)
		ret.x[i] = src[len - 1 - i];
	v_len(&ret, len);
	return (ret);
}

/*
**	try to read an asn1 der integer sequence from t_read,
**	if data are valid, store the number of varint decoded in *nb_varint,
**	and return a varint fresh malloc array filled with decoded data.
*/

t_varint				*v_asn1_int_seq_der_d(int *nb_varint, t_read *r)
{
	t_der_d		ori;
	t_varint	*ret;
	t_der_d		*cur;

	ori.id = -1;
	ori.st_h = (uint8_t *)r->msg;
	ori.nxt = NULL;
	if ((*nb_varint = check_and_count(&ori, r)) == -1)
		return (NULL);
	ret = (t_varint *)malloc(sizeof(t_varint) * *nb_varint);
	cur = &ori;
	while ((cur = cur->nxt) != NULL)
		ret[cur->id] = v_load(cur->st, cur->len);
	free_der_d(&ori);
	return (ret);
}
