#include "libft.h"

/*
** v_gcd et v_eea attendent des nombres positifs en entrée
*/

t_varint		v_gcd(t_varint a, t_varint b)
{
	t_varint		r[2];
	t_varint		tmp;

	a.sign = 1;
	b.sign = 1;
	v_sort(&a, &b);
	r[0] = a;
	r[1] = b;	
	while (!is_g_v(0, r[1]))
	{
		tmp = v_mod(r[0],  r[1], true);
		r[0] = r[1];
		r[1] = tmp;
	}
	return (r[0]);
}

void		v_eea(t_varint *coef_r0, t_varint a, t_varint b)
{
	t_varint	r[2]; // deux derniers restes
	t_varint	coef_r1[2]; // coef alpha et beta de r[1]
	t_varint	tmp[2];	

	a.sign = 1;
	b.sign = 1;
	v_sort(&a, &b);
	r[0] = a;
	coef_r0[0] = g_v[1];
	coef_r0[1] = g_v[0];
	r[1] = b;	
	coef_r1[0] = g_v[0];
	coef_r1[1] = g_v[1];

	while (!is_g_v(0, r[1]))
	{
		tmp[0] = v_mod(r[0], r[1], true);
		tmp[1] = v_div(v_sub(r[0], tmp[0]), r[1]);
		r[0] = r[1];
		r[1] = tmp[0];

		tmp[0] = v_sub(coef_r0[0], v_mul(tmp[1], coef_r1[0]));
		tmp[1] = v_sub(coef_r0[1], v_mul(tmp[1], coef_r1[1]));

		coef_r0[0] = coef_r1[0];
		coef_r0[1] = coef_r1[1];
		coef_r1[0] = tmp[0];
		coef_r1[1] = tmp[1];
	}
}

t_varint		v_inv(t_varint v, t_varint mod)
{
	t_varint	tmp[2];

	if (!is_g_v(1, v_gcd(v, mod))
		&& ft_dprintf(2, "%s%s%s", KRED, V_INV_MOD_ERR, KNRM))
		return (g_v[3]);
	v_eea(tmp, v, mod);
	if (v_cmp(v, "-gt", mod))
		return (tmp[0]);
	return (tmp[1]);
}
