#include "libft.h"


static int8_t			v_check_add_sub(t_varint a, t_varint b)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	sup = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 1) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_ADD_OVFL, KNRM))
		return (3);
	return (-1);
}

static int8_t			v_check_mul(t_varint a, t_varint b)
{
	int64_t	mb_pow[2];

	mb_pow[0] = v_maxbin_pow(a);
	mb_pow[1] = v_maxbin_pow(b);
	if (1 + (mb_pow[0] + 1 + mb_pow[1] + 1) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_MUL_OVFL, KNRM))
		return (3);
	return (-1);
}

static int8_t		v_check_div_mod(t_varint dividend, t_varint divisor)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	if (is_g_v(0, divisor)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (3);
	mb_pow[0] = v_maxbin_pow(dividend);
	mb_pow[1] = v_maxbin_pow(divisor);
	sup = (mb_pow[0] >= mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 2) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_MOD_OVFL, KNRM))
		return (3);
	return (-1);
}

static int8_t		v_check_exp(t_varint v, t_varint e)
{
	int64_t	mb_pow[2];
	uint64_t	e64;
	int8_t	i;

	if (e.sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (3);
	if (e.len * sizeof(V_TYPE) > 8
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_LIM, KNRM))
		return (3);
	e64 = 0;
	i = -1;
	while (++i < e.len)
		e64 += (uint64_t)e.x[i] << V_BIT_LEN * i;
	mb_pow[0] = v_maxbin_pow(v);
	mb_pow[1] = v_maxbin_pow(e);
	if (1 + ((mb_pow[0] + 1)* e64) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXP_OVFL, KNRM))
		return (3);
	if (is_g_v(0, e))
		return (1);
	if (is_g_v(0, v))
		return (0);
	return (-1);
}

static int8_t		v_check_expmod(t_varint v, t_varint e, t_varint mod)
{
	int64_t	mb_pow[2];
	int64_t	sup;

	mb_pow[0] = 2 * (v_maxbin_pow(v) + 1);
	mb_pow[1] = 2 * (v_maxbin_pow(mod) + 1);
	sup = (mb_pow[0] > mb_pow[1]) ? mb_pow[0] : mb_pow[1];
	if (1 + (sup + 6) / V_BIT_LEN > V_MAX_LEN
		&& ft_dprintf(2, "%s%s%s", KRED, V_EXPMOD_OVFL, KNRM))
		return (3);
	if (e.sign == -1
		&& ft_dprintf(2, "%s%s%s", KRED, V_NEG_POW, KNRM))
		return (3);
	if (is_g_v(0, mod)
		&& ft_dprintf(2, "%s%s%s", KRED, V_DIV_BY_0, KNRM))
		return (3);
	if (is_g_v(0, e))
		return (1);
	if (is_g_v(0, v))
		return (0);
	return (-1);
}

/*
**	if v_check return a number 0 <= n <= 3 
** to varint operator scop
**	then operator return directly g_v[n]
**	else if v_check return -1
**	operator compute its operands
*/

int8_t				v_check(t_varint a, t_varint b, t_varint m, char *op)
{

	if (is_g_v(3, a) || is_g_v(3, b) || is_g_v(3, m))
		return (3);
	if ((a.len <= 0 || a.len > V_MAX_LEN
		|| b.len <= 0 || b.len > V_MAX_LEN
		|| m.len <= 0 || m.len > V_MAX_LEN)
		&& ft_dprintf(2, "%s%s%s", KRED, V_BAD_LEN, KNRM))
		return (3);
	if (op && !ft_strcmp("add_sub", op))
		return (v_check_add_sub(a, b));
	if (op && !ft_strcmp("mul", op))
		return (v_check_mul(a, b));
	if (op && !ft_strcmp("exp", op))
		return (v_check_exp(a, b));
	if (op && !ft_strcmp("div_mod", op))
		return (v_check_div_mod(a, b));
	if (op && !ft_strcmp("expmod", op))
		return (v_check_expmod(a, b, m));
//	printf("TOUT VA BIEN == -1\n");	
	return (-1);
}
