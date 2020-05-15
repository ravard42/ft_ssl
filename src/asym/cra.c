/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cra.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 19:52:59 by ravard            #+#    #+#             */
/*   Updated: 2020/05/15 19:53:01 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Chinese Remainder Algorithm (decryption speed up)
*/

/*
** CRA OVLF NOTE : call v_expmod_check
*/

/*
** t_varint *rsak : version, n, e, d, p, q, dp, dq, qinv
**	t_varint	tmp	: cp, cq, m1, m2, h, m
**
**	cp = c [mod(p)]
**	cq = c [mod(q)]
**	m1 = cp^dp [mod(p)]
**	m2 = cq^dq [mod(q)]
**	h = qinv*(m1-m2) [mod(p)]
**	m = m2 + h*q [mod(n=p*q)]
*/

t_varint		cra(t_varint *vdata, t_varint *rsak)
{
	t_varint		tmp[6];

	if (!v_check(vdata, rsak + 3, rsak + 1, "expmod"))
		return (g_v[3]);
	tmp[0] = v_mod(*vdata, rsak[4], true, false);
	tmp[1] = v_mod(*vdata, rsak[5], true, false);
	tmp[2] = v_expmod(tmp[0], rsak[6], rsak[4], false);
	tmp[3] = v_expmod(tmp[1], rsak[7], rsak[5], false);
	tmp[4] = v_sub(tmp[2], tmp[3], false);
	tmp[4] = v_mul(tmp[4], rsak[8], false);
	tmp[4] = v_mod(tmp[4], rsak[4], true, false);
	tmp[5] = v_mul(tmp[4], rsak[5], false);
	tmp[5] = v_add(tmp[5], tmp[3], false);
	tmp[5] = v_mod(tmp[5], rsak[1], true, false);
	return (tmp[5]);
}
