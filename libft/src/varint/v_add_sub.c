#include "libft.h"

int8_t				add_carry(V_TYPE a, V_TYPE b, int8_t c)
{
	int8_t			d;

	d = ((a & 1) + (b & 1) + (c & 1)) >> 1 & 1;
	return ((d + (a >> 1) + (b >> 1)) >> (V_BIT_LEN - 1));
}

/*
** a >= 0 et b >= 0
*/

static t_varint	v_add_pos(t_varint a, t_varint b)
{
	t_varint			ret;
	V_LEN_TYPE		len;
	V_LEN_TYPE		i;
	int8_t			c;

	ret = g_v[0];
	len = (a.len >= b.len) ? a.len : b.len;
	c = 0;
	i = -1;
	while (++i < len)
	{
		ret.x[i] = a.x[i] + b.x[i] + c;
		c = add_carry(a.x[i], b.x[i], c);
	}
	ret.len = (c) ? i + 1 : i;
	ret.x[i] += (c) ? c : 0;
	return (ret);
}

/*
** a >= b >= 0
*/

static t_varint	v_sub_pos(t_varint a, t_varint b)
{
	t_varint			ret;
	V_LEN_TYPE		len;
	V_LEN_TYPE		i;
	uint8_t			c;

	ret = g_v[0];
	len = a.len;
	c = 0;
	i = -1;
	while (++i < len)
	{
		ret.x[i] = a.x[i] - (b.x[i] + c);
		c = (a.x[i] >= b.x[i] + c) ? 0 : 1;
	}
	v_len(&ret);
	return (ret);
}

t_varint				v_add(t_varint a, t_varint b)
{
	t_varint			ret;
	bool				tmp;
	
	if (v_check(a, b, g_v[0], "add_sub") == 3)
		return (g_v[3]);
	if (a.sign == b.sign)
	{
		ret = v_add_pos(v_abs(a), v_abs(b));
		ret.sign = a.sign;
	}
	else
	{
		tmp = v_cmp(v_abs(a), "-ge", v_abs(b));
		ret = tmp ? v_sub_pos(v_abs(a), v_abs(b))
			: v_sub_pos(v_abs(b), v_abs(a));
		ret.sign = tmp ? a.sign : b.sign;
	}
	return (ret);
}

t_varint			v_sub(t_varint a, t_varint b)
{
	b.sign *= -1;
	return (v_add(a, b));
}
