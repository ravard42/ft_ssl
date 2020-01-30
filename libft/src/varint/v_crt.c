/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_crt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 05:48:50 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 02:47:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** about crt[8]
**
**	index 		data
**
**		0			cp
**		1			dp
**	 	2			cq
**	 	3			dq
**	 	4			qinv
**	 	5			m1
**	 	6			m2
**	 	7			h
*/

t_varint		v_crt(t_varint v, t_varint e, t_varint p, t_varint q)
{
	t_varint				n;
	t_varint				crt[8];

	n = v_mul(p, q, true);
	if (!v_check(&v, &e, &n, "crt"))
		return (g_v[3]);
	if (is_g_v(0, &e))
		return (g_v[1]);
	crt[0] = v_mod(v, p, true, false);
	crt[1] = v_mod(e, v_sub(p, g_v[1], false), true, false);
	crt[2] = v_mod(v, q, true, false);
	crt[3] = v_mod(e, v_sub(q, g_v[1], false), true, false);
	crt[4] = v_inv(q, p);
	crt[5] = v_expmod(crt[0], crt[1], p, true);
	crt[6] = v_expmod(crt[2], crt[3], q, true);
	crt[7] = v_mod(v_mul(crt[4], v_sub(crt[5], crt[6], true), true),
			p, true, false);
	return (v_mod(v_add(crt[6], v_mul(crt[7], q, true), true), n, true, false));
}
