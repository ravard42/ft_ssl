/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:07:20 by ravard            #+#    #+#             */
/*   Updated: 2019/06/30 12:43:57 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	md5_init(t_hash *hash)
{
	static uint32_t		tmp[64] = {7, 12, 17, 22, 5, 9, 14, 20,
							4, 11, 16, 23, 6, 10, 15, 21};
	int					i;

	i = -1;
	while (++i < 64)
	{
		hash->s[i] = tmp[4 * (i / 16) + i % 4];
		hash->k[i] = floor(fabs(sin(i + 1) * pow(2, 32)));
	}
	hash->h[0] = 0x67452301;
	hash->h[1] = 0xEFCDAB89;
	hash->h[2] = 0x98BADCFE;
	hash->h[3] = 0x10325476;
}
