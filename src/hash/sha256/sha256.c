/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:44:50 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:54:49 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int		sha256(t_parse *p)
{
	int64_t			i;

	if (!hash_padding(p))
		return (0);
	i = 0;
	sha256_init(&p->h);
	while (i < p->w.len / 64)
		sha256_block_hash(&p->h, p->w.msg, &i);
	if (p->cmd.endian & 4)
		multi_bswap32(p->h.h, 8);
	if (!p->h.pbkdf)
		print_format(p, &p->h);
	free_p(p);
	return (1);
}
