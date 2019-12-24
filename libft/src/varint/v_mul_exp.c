#include "libft.h"

/*
**	x * y = (a + b) * (c + d)
**	
**	|upper = a * c||lower = b * d|
**			  |mid[0] = a*d|
**			  |mid[1] = b*c|
**
*/

static V_TYPE 		upper(V_TYPE x, V_TYPE y)
{
	V_TYPE			tmp[4];
	V_TYPE			upper;
	V_TYPE			mid[2];
	V_TYPE			lower;
	V_TYPE			ovfl;

	tmp[0] = x >> V_BIT_LEN / 2;
	tmp[1] = x & V_MID_INF;
	tmp[2] = y >> V_BIT_LEN / 2;
	tmp[3] = y & V_MID_INF;
	upper = tmp[0] * tmp[2];
	mid[0] = tmp[0] * tmp[3];
	mid[1] = tmp[1] * tmp[2];
	lower = tmp[1] * tmp[3];
	ovfl = upper
		+ (mid[0] >> V_BIT_LEN / 2) + (mid[1] >> V_BIT_LEN / 2)
		+ (((mid[0] & V_MID_INF) + (mid[1] & V_MID_INF)
			+ (lower >> V_BIT_LEN / 2)) >> V_BIT_LEN / 2);
	return (ovfl);
}

static void		partial_mul(t_varint *p_mul, t_varint a, V_TYPE bxj)
{
	V_LEN_TYPE		i;
	V_TYPE			ovfl;
	V_TYPE			tmp;
	int8_t			c;

	c = 0;
	ovfl = 0;
	i = -1;
	while (++i < a.len)
	{
		tmp = a.x[i] * bxj;	
		p_mul->x[p_mul->len] = tmp + ovfl + c;
		p_mul->len++;
		c = add_carry(tmp, ovfl, c);
		ovfl = upper(a.x[i], bxj);
	}
	if (ovfl + c > 0)
	{
		p_mul->x[p_mul->len] = ovfl + c;
		p_mul->len += 1;
	}
	v_len(p_mul);
}

t_varint				v_mul(t_varint a, t_varint b)
{
	t_varint 	ret;
	t_varint 	p_mul;
	V_LEN_TYPE	j;
	int8_t		sign;

	if (v_check(a, b, g_v[0], "mul") == 3)
		return (g_v[3]);
	sign = a.sign * b.sign;
	a.sign = 1;
	b.sign = 1;
	ret = g_v[0];
	j = -1;
	while (++j < b.len)
	{
		p_mul = g_v[0];
		p_mul.len = j;
		partial_mul(&p_mul, a, b.x[j]);
		ret = v_add(ret, p_mul);
		if (is_g_v(3, ret))
			return (ret);
	}
	ret.sign = sign;
	return (ret);
}

/*
** i : varint index
** j : bit index
*/

t_varint			v_exp(t_varint v, t_varint e)
{
	V_LEN_TYPE					i;
	int8_t						j;
	t_varint						ret;

	if ((j = v_check(v, e, g_v[0], "exp")) != -1)
		return (g_v[j]);
	j = V_BIT_LEN - 1;
	while (!(e.x[e.len - 1] >> j & 1))
		j--;
	ret = v;
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			ret = v_mul(ret, ret);
			if (e.x[i] >> j & 1)
				ret = v_mul(ret, v);
		}
	}
	return (ret);
}
