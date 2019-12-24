/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_triple.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:15:44 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 10:16:08 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t			des_triple(uint64_t x, t_parse *p)
{
	p->s.id_k = (p->o[6]) ? 2 : 1;
	x = (p->o[6]) ? des_block_d(x, p) : des_block_e(x, p);
	p->s.id_k = 1;
	x = (p->o[6]) ? des_block_d(x, p) : des_block_e(x, p);
	p->s.id_k = (p->o[6]) ? 0 : 2;
	x = (p->o[6]) ? des_block_d(x, p) : des_block_e(x, p);
}
