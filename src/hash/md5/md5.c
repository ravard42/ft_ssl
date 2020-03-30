/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:07:23 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:44:15 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		md5(t_parse *p)
{
	int64_t		i;

	if (!hash_padding(p))
		return (0);
	i = 0;
	md5_init(&p->h);
	while (i < p->w.len / 64)
		md5_block_hash(&p->h, p->w.msg, &i);
	if (p->cmd.endian & 4)
		multi_bswap32(p->h.h, 4);
	if (!p->h.pbkdf)
		print_format(p, &p->h);
	free_p(p, 3);
	return (1);
}
