/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:14:57 by ravard            #+#    #+#             */
/*   Updated: 2019/09/11 10:15:16 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t		f(t_parse *p, uint8_t i)
{
	uint64_t		tmp;
	uint32_t		ret;

	tmp = expansion_perm(p->s.r, p->cmd.endian);
	tmp ^= p->s.sub_k[i + 16 * p->s.id_k];
	ret = s_boxes(tmp);
	ret = round_perm(ret);
	return (ret);
}

void				des_round(t_parse *p, uint8_t i)
{
	uint32_t		tmp;

	tmp = p->s.r;
	p->s.r = p->s.l ^ f(p, i);
	p->s.l = tmp;
}
