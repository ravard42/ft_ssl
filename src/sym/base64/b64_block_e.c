/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b64_block_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:47:57 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:48:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t		be_transpo(uint32_t x)
{
	return (x >> 24);
}

uint32_t		b64_block_e(uint32_t in, uint8_t k, uint8_t b_endian)
{
	char					tmp[4];
	uint32_t				out;
	static uint32_t			(*endian)(uint32_t);

	endian = (b_endian) ? be_transpo : bswap32;
	in = (b_endian) ? in : endian(in);
	if (k == 3)
	{
		tmp[0] = g_tab64[endian(in >> 2 & 0x3f000000)];
		tmp[1] = g_tab64[endian(in << 4 & 0x3f000000)];
		tmp[2] = g_tab64[endian(in << 10 & 0x3f000000)];
		tmp[3] = g_tab64[endian(in << 16 & 0x3f000000)];
	}
	if (k == 2 || k == 1)
	{
		in &= (k == 2) ? 0xFFFF0000 : 0xFF000000;
		tmp[0] = g_tab64[endian(in >> 2 & 0x3f000000)];
		tmp[1] = g_tab64[endian(in << 4 & 0x3f000000)];
		tmp[2] = (k == 2) ?
			g_tab64[endian(in << 10 & 0x3f000000)] : '=';
		tmp[3] = '=';
	}
	ft_memcpy(&out, tmp, 4);
	return (out);
}
