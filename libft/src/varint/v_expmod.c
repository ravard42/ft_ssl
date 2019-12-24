#include "libft.h"

static void			sqr_mul_mod(t_varint *ret, t_varint *v, t_varint *mod, bool eucl)
{
	if (v == NULL)
	{
		*ret = v_mul(*ret, *ret);
		*ret = v_mod(*ret, *mod, eucl);
	}
	else
	{
		*ret = v_mul(*ret, *v);
		*ret = v_mod(*ret, *mod, eucl);
	}
}

t_varint				v_expmod(t_varint v, t_varint e, t_varint mod, bool eucl)
{
	V_LEN_TYPE		i;
	int8_t			j;
	t_varint			ret;

	if ((j = v_check(v, e, mod, "expmod")) != -1)
		return (g_v[j]);
	j = V_BIT_LEN - 1;
	while (((V_TYPE)e.x[e.len - 1] >> j & 1) == 0)
		j--;
	ret = v_mod(v, mod, true);
	i = e.len;
	while (--i >= 0)
	{
		j = (i == e.len - 1) ? j : V_BIT_LEN;
		while (--j >= 0)
		{
			sqr_mul_mod(&ret, NULL, &mod, eucl);
			if (e.x[i] >> j & 1)
				sqr_mul_mod(&ret, &v, &mod, eucl);
		}
	}
	return (ret);
}
