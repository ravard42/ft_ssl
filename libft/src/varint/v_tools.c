#include "libft.h"

bool				is_g_v(int8_t i, t_varint v)
{
	if (i == 3)
	{
		if (v.sign == 0
			&& ft_dprintf(2, "%s%s%s", KRED, V_ERR, KNRM))
			return (true);
		return (false);
	}
	v.sign = (i == 0) ? 1 : v.sign;
	if (v.sign == 1 && v.len == 1 && v.x[0] == (V_TYPE)i)
		return (true);
	return (false);
}

void			v_len(t_varint *v)
{
	V_LEN_TYPE		i;

	i = V_MAX_LEN;
	while (--i > 0)
		if (v->x[i])
			break ;
	v->len = i + 1;
}

t_varint		v_init(char sign, V_TYPE *src, V_LEN_TYPE len)
{
	t_varint		v;
	V_LEN_TYPE		i;

	v = g_v[0];
	if ((len <= 0 || len > V_MAX_LEN)
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_LEN, KNRM))
		return (g_v[3]);
	v.sign = sign;
	i = -1;
	while (++i < len)
		v.x[i] = src[i];
	v_len(&v);
	return (v);
}

void			v_sort(t_varint *a, t_varint *b)
{
	t_varint	tmp;

	if (v_cmp(*a, "-lt", *b))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void		v_print(t_varint *v, char *name, int64_t number, char *col)
{
	V_LEN_TYPE		i;

	if (v_check(*v, g_v[0], g_v[0], NULL) == 3)
		return;
	if (number == -2)
		ft_dprintf(2, "%s<---VARINT %s------->%s\n", col, name, KNRM);
	else if (number >= -1)
		ft_dprintf(2, "%s<---VARINT %s %ld------->%s\n", col, name, number, KNRM);
	ft_dprintf(2, "v->sign = %hd\n", v->sign);
	ft_dprintf(2, "v->len = %d\n", v->len);
	i = v->len;
	while (--i != -1)
		//ft_dprintf(2, "(i, x) = (%lu, %02lx)\n", i, v->x[i]);
		ft_dprintf(2, "(i, x) = (%lu, %lx)\n", i, v->x[i]);
	ft_dprintf(2, "%s<---------------------->\n%s", col, KNRM);
}
