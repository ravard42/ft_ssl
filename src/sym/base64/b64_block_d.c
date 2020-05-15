/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_block_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:45:01 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 13:49:33 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static bool			is_whitespace(char c)
{
	uint8_t i;

	i = -1;
	while (++i < 4 && c != g_whitespace[i])
		;
	if (i != 4)
		return (true);
	return (false);
}

void				del_whitespaces(t_read *r)
{
	int64_t		ws_nb;
	int64_t		i;

	ws_nb = 0;
	i = -1;
	while (++i < r->len)
	{
		if (is_whitespace(r->msg[i]))
			ws_nb++;
		else
			r->msg[i - ws_nb] = r->msg[i];
	}
	r->len -= ws_nb;
}

static bool			b64_d_check(uint32_t in, uint8_t b_endian)
{
	bool				equal;
	int8_t				pos;
	int8_t				i;
	uint8_t				ascii_id;
	static uint32_t		(*endian)(uint32_t);

	endian = (b_endian) ? be_transpo : bswap32;
	equal = 0;
	pos = -1;
	while (++pos < 4)
	{
		ascii_id = endian((in << (pos * 8)) & 0xFF000000);
		i = g_rev_tab64[ascii_id];
		if (i == 64)
			equal = 1;
		if (i == 80 && ft_dprintf(2, g_ssl_str[B64_ERR_0], KRED, KNRM))
			return (false);
		else if (equal && i != 64
				&& ft_dprintf(2, g_ssl_str[B64_ERR_1], KRED, KNRM))
			return (false);
		else if (i == 64 && (pos == 0 || pos == 1)
				&& ft_dprintf(2, g_ssl_str[B64_ERR_2], KRED, KNRM))
			return (false);
	}
	return (true);
}

uint32_t			b64_block_d(uint32_t in, uint8_t *k, uint8_t b_endian)
{
	uint32_t		out;
	int32_t			i;
	uint8_t			ascii_id;
	static uint32_t (*endian)(uint32_t);

	endian = (b_endian) ? be_transpo : bswap32;
	in = (b_endian) ? in : bswap32(in);
	if (!b64_d_check(in, b_endian))
		return (0xFFFFFFFF);
	out = 0;
	*k = -1;
	while (++(*k) < 4)
	{
		ascii_id = endian((in << (*k * 8)) & 0xFF000000);
		i = g_rev_tab64[ascii_id];
		if (i == 64)
			break ;
		i <<= (26 - (*k * 6));
		out |= (b_endian) ? (uint32_t)i : bswap32(i);
	}
	(*k)--;
	return (out);
}
