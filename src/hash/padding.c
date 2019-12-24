/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:10:39 by ravard            #+#    #+#             */
/*   Updated: 2019/06/28 20:11:38 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*hash_padding(t_parse *p)
{
	uint64_t	q;
	uint64_t	r;
	uint64_t	msg_bit_len;

	msg_bit_len = p->r.len * 8;
	q = msg_bit_len / 512;
	r = msg_bit_len % 512;
	p->w.len = (r >= 448) ? (q + 2) * 64 : (q + 1) * 64;
	if (!(p->w.msg = (char *)ft_memalloc(sizeof(char) * (p->w.len))))
		return (NULL);
	ft_memcpy(p->w.msg, p->r.msg, p->r.len);
	p->w.msg[p->r.len] = -128;
	msg_bit_len = (p->cmd.endian & 4) ? bswap64(msg_bit_len) : msg_bit_len;
	ft_memcpy(p->w.msg + p->w.len - 8, &msg_bit_len, 8);
	if (p->cmd.endian & 4)
		multi_bswap32((uint32_t *)p->w.msg, p->w.len / 4);
	return (p->w.msg);
}
