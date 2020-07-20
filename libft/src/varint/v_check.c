/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:39:02 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:35:25 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool				v_len_check(t_varint *v)
{
	int16_t		tmp;

	if ((V_MAX_LEN <= 0 || V_MAX_LEN % 8 != 0 || V_MAX_LEN > 4096)
		&& ft_dprintf(2, g_v_sterr[V_ERR_MAXLEN], KRED, KNRM))
		exit(0);
	if ((v->len <= 0 || v->len > V_MAX_LEN)
		&& ft_dprintf(2, g_v_sterr[V_ERR_LEN_0], KRED, KNRM))
		return (false);
	tmp = v->len;
	v_len(v, V_MAX_LEN);
	if (v->len != tmp && ft_dprintf(2, g_v_sterr[V_ERR_LEN_1], KRED, KNRM))
		return (false);
	return (true);
}

/*
** v_check verify that  a, b and m are valid varint variables:
** 1] sign == -1 or sign == 1
** 2] their len are consistent
**
** morevover if op make sense:
** v_check call v_<op>_check which estimates
** if the resultat of op will not overflow V_MAX_LEN
** and verify that the operation is well defined
** (ex: divison by 0 same for a negative exponent)
*/

static const char	*g_op_name[] = {"left_shift", "add", "mul", "exp",
	"div", "expmod", "eea", NULL};
static t_op_check	g_op_check[] = {v_lshift_check, v_add_check, v_mul_check,
	v_exp_check, v_div_check, v_expmod_check, v_eea_check};

bool					v_check(t_varint *a, t_varint *b, t_varint *m, char *op)
{
	t_varint		*v_tab[3];
	int				i;

	v_tab[0] = a;
	v_tab[1] = b;
	v_tab[2] = m;
	i = -1;
	while (++i < 3)
	{
		if (v_tab[i])
		{
			is_g_v(0, v_tab[i]);
			if (is_g_v(3, v_tab[i]))
				return (false);
			if (!v_len_check(v_tab[i]))
				return (false);
		}
	}
	i = -1;
	while (op && g_op_name[++i] && ft_strcmp(g_op_name[i], op))
		;
	if (op && g_op_name[i])
		return (g_op_check[i](v_tab));
	return (true);
}
