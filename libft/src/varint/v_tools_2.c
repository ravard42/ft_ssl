#include "libft.h"

int64_t					v_maxbin_pow(t_varint v)
{
	int64_t	j;

	if (is_g_v(0, v))
		return (-1);	
	j = V_BIT_LEN - 1;
	while (!(v.x[v.len - 1] >> j & 1))
		j--;
	j += (v.len > 1) ? (v.len - 1) * V_BIT_LEN : 0;
	return (j);
}

t_varint				v_inc(t_varint a)
{
	a = v_add(a, g_v[1]);
	return (a);
}

t_varint				v_dec(t_varint a)
{
	a = v_sub(a, g_v[1]);
	return (a);
}

t_varint		v_abs(t_varint v)
{
	v.sign = 1;
	return (v);
}

t_varint		v_rand_n(int fd, V_LEN_TYPE len)
{
	V_TYPE		rand_n[len];
	V_LEN_TYPE		i;
	t_varint		n;

	i = -1;
	while (++i < len)
		rand_n[i] = ft_rand(fd, 0, 0);
	n = v_init(1, rand_n, len);
	return (n);
}
