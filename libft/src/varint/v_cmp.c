#include "libft.h"

static bool		v_lt_pos(t_varint a, t_varint b)
{
	V_LEN_TYPE	i;
	
	if (a.len > b.len)
		return (false);
	if (b.len > a.len)
		return (true);
	i = a.len;
	while (--i > -1 && a.x[i] == b.x[i])
		;
	if (i == -1)
		return (false);
	if (a.x[i] > b.x[i])
		return (false);
	return (true);
}

static bool		v_lt_neg(t_varint a, t_varint b)
{
	V_LEN_TYPE	i;

	if (a.len > b.len)
		return (true);
	if (b.len > a.len)
		return (false);
	i = a.len;
	while (--i > -1 && a.x[i] == b.x[i])
		;
	if (i == -1)
		return (false);
	if (a.x[i] > b.x[i])
		return (true);
	return (false);
}

static bool		v_lt(t_varint a, t_varint b)
{

	if (is_g_v(0, a) && is_g_v(0, b))
		return (false);
	if (a.sign == 1 && b.sign == -1)
		return (false);
	if (a.sign == -1 && b.sign == 1)
		return (true);
	if (a.sign == 1 && b.sign == 1)
		return (v_lt_pos(a, b));
	return (v_lt_neg(a, b));
}

static bool		v_eq(t_varint a, t_varint b)
{
	V_LEN_TYPE	i;

	if (is_g_v(0, a) && is_g_v(0, b))
		return (true);
	if (a.sign != b.sign)
		return (false);
	if (a.len > b.len)
		return (false);
	if (b.len > a.len)
		return (false);
	i = a.len;
	while (--i > -1 && a.x[i] == b.x[i])
		;
	if (i == -1)
		return (true);
	return (false);
}

bool	v_cmp(t_varint a, char *cmp, t_varint b)
{
	if (v_check(a, b, g_v[0], NULL) == 3)
		return (false);
	if (!ft_strcmp("-eq", cmp))
		return (v_eq(a, b));
	if (!ft_strcmp("-ne", cmp))
		return (!v_eq(a, b));
	if (!ft_strcmp("-lt", cmp))
		return (v_lt(a, b));
	if (!ft_strcmp("-ge", cmp))
		return (!v_lt(a, b));
	if (!ft_strcmp("-le", cmp))
		return (v_lt(a, b) || v_eq(a, b));
	if (!ft_strcmp("-gt", cmp))
		return (!(v_lt(a, b) || v_eq(a, b)));
	ft_dprintf(2, "%sbad comparaison operator\n%s", KRED, KNRM);
	return (false);
}
