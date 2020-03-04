/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_gcd_eea_inv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:06:22 by ravard            #+#    #+#             */
/*   Updated: 2020/01/25 02:27:40 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


/*
** V_GCD OVFL NOT
**
** just one v_mod in there so GCD isn't concerned by ovfl
**
*/

t_varint		v_gcd(t_varint a, t_varint b, bool check)
{
	t_varint		r[2];
	t_varint		tmp;

	if (check && !v_check(&a, &b, NULL, "gcd"))
		return (g_v[3]);
	a.sign = 1;
	b.sign = 1;
	v_sort(&a, &b, NULL);
	r[0] = a;
	r[1] = b;
	while (!is_g_v(0, r + 1))
	{
		tmp = v_mod(r[0], r[1], true, false);
		r[0] = r[1];
		r[1] = tmp;
	}
	return (r[0]);
}

/*
** V_EEA OVFL NOTE
**
** we know that final resultat (coef_r0, coef_r0 + 1) can be contained in the same varint size that inputs
** however when processing v_mul algo in eea it could overflow in the way we handle carry (32-bit * 32-bit in 64-bit)
** (cf v_mul algo -> u64 = (uint64_t *)((uint32_t *)ret->x + i + j);)
** let alen32, blen32 and maxlen32 that represent the number of uint32_t chunk necessary to contained respectively a, b and V_MAX_LEN chunks 
**	we want max32 >= alen32 + blen32
*/

bool			v_eea_check(t_varint *v[3])
{
	int64_t	len32[3];

	len32[0] = v[0]->len / 4;
	len32[0] += (v[0]->len % 4) ? 1 : 0;
	len32[1] = v[1]->len / 4;
	len32[1] += (v[1]->len % 4) ? 1 : 0;
	len32[2] = V_MAX_LEN / 4;
	if (len32[0] + len32[1] > len32[2]
		&& ft_dprintf(2, "%s%s%s", KRED, V_EEA_OVFL, KNRM))
		return (false);
	return (true);
}

static void	process(t_varint *coef_r0, t_varint *coef_r1, t_varint *r)
{
	t_varint	tmp[2];

	tmp[0] = v_mod(r[0], r[1], true, false);
	tmp[1] = v_div(v_sub(r[0], tmp[0], false), r[1], false);
	r[0] = r[1];
	r[1] = tmp[0];
	tmp[0] = v_sub(coef_r0[0], v_mul(tmp[1], coef_r1[0], false), false);
	tmp[1] = v_sub(coef_r0[1], v_mul(tmp[1], coef_r1[1], false), false);
	coef_r0[0] = coef_r1[0];
	coef_r0[1] = coef_r1[1];
	coef_r1[0] = tmp[0];
	coef_r1[1] = tmp[1];
}

/*
** r[2]			: deux derniers restes de l'algo d'Euclide
** coef_r0[2]	: coef alpha et beta de r[0] (allocated outside)
** coef_r1[2]	: coef alpha et beta de r[1]
*/

void			v_eea(t_varint *coef_r0, t_varint a, t_varint b, bool check)
{
	int8_t	sign[3];
	t_varint	r[2];
	t_varint	coef_r1[2];

	if (check && !v_check(&a, &b, NULL, "eea"))
		return ;
	sign[2] = v_sort(&a, &b, sign);
	r[0] = a;
	r[1] = b;
	coef_r0[0] = g_v[1];
	coef_r0[1] = g_v[0];
	coef_r1[0] = g_v[0];
	coef_r1[1] = g_v[1];
	while (!is_g_v(0, r + 1))
		process(coef_r0, coef_r1, r);
	coef_r0[0].sign *= (sign[0] != a.sign) ? -1 : 1;
	(coef_r0[1]).sign *= (sign[1] != a.sign) ? -1 : 1;
	if (sign[2])
	{
		r[0] = coef_r0[0];
		coef_r0[0] = coef_r0[1];
		coef_r0[1] = r[0];
	}	
}

/*
** V_INV OVFL NOT
**
** same as EEA
**
*/

t_varint		v_inv(t_varint v, t_varint mod, bool check)
{
	t_varint	tmp[2];
	t_varint	gcd;

	if (check && !v_check(&v, &mod, NULL, "eea"))
		return (g_v[3]);
	gcd = v_gcd(v, mod, false);
	if (!is_g_v(1, &gcd)
		&& ft_dprintf(2, "%s%s%s", KRED, V_INV_MOD_ERR, KNRM))
		return (g_v[3]);
	v_eea(tmp, v, mod, false);
	if (tmp[0].sign == -1)
		tmp[0] = v_mod(tmp[0], mod, true, false);
	return (tmp[0]);
}
