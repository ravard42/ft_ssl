/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:14:57 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:03:09 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint32_t		f(t_sym *s, uint8_t i)
{
	uint64_t		tmp;
	uint32_t		ret;

	tmp = expansion_perm(s);
	tmp ^= s->sub_k[i + 16 * s->id_k];
	ret = s_boxes(tmp);
	ret = round_perm(ret);
	return (ret);
}

void				des_round(t_sym *s, uint8_t i)
{
	uint32_t		tmp;

	tmp = s->r;
	s->r = s->l ^ f(s, i);
	s->l = tmp;
}
