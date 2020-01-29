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
** v_gcd et v_eea sont ramené à des nombres positifs par soucis de commodité
*/

t_varint		v_gcd(t_varint a, t_varint b)
{
	t_varint		r[2];
	t_varint		tmp;

	if (!v_check(&a, &b, &g_v[0], "gcd"))
		return (g_v[3]);
	if (a.sign != 1 || b.sign != 1)
	{
		ft_dprintf(2, "%sat least one sign switch to 1 in gcd%s\n",
				KYEL, KNRM);
		a.sign = 1;
		b.sign = 1;
	}
	v_sort(&a, &b, false);
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

static void		verif_and_sort(t_varint *coef_r0, t_varint *coef_r1,
		t_varint *a, t_varint *b)
{
	if (a->sign != 1 || b->sign != 1)
	{
		ft_dprintf(2, "%sat least one sign switch to 1 in eea%s\n",
				KYEL, KNRM);
		a->sign = 1;
		b->sign = 1;
	}
	v_sort(a, b, false);
	coef_r0[0] = g_v[1];
	coef_r0[1] = g_v[0];
	coef_r1[0] = g_v[0];
	coef_r1[1] = g_v[1];
}

/*
** r[2]			: deux derniers restes
** coef_r1[2]	: coef alpha et beta de r[1]
*/

void			v_eea(t_varint *coef_r0, t_varint a, t_varint b)
{
	t_varint	r[2];
	t_varint	coef_r1[2];
	t_varint	tmp[2];

	if (!v_check(&a, &b, &g_v[0], "eea"))
		return ;
	verif_and_sort(coef_r0, coef_r1, &a, &b);
	r[0] = a;
	r[1] = b;
	while (!is_g_v(0, r + 1))
	{
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
}

t_varint		v_inv(t_varint v, t_varint mod)
{
	t_varint	tmp[2];
	t_varint	gcd;

	if (!v_check(&v, &g_v[0], &mod, "inv"))
		return (g_v[3]);
	gcd = v_gcd(v, mod);
	if (!is_g_v(1, &gcd)
		&& ft_dprintf(2, "%s%s%s", KRED, V_INV_MOD_ERR, KNRM))
		return (g_v[3]);
	v_eea(tmp, v, mod);
	if (v_cmp(&v, "-gt", &mod, true))
		return (tmp[0]);
	return (tmp[1]);
}
