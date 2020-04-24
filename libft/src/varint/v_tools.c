/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 04:22:35 by ravard            #+#    #+#             */
/*   Updated: 2020/01/30 07:06:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool			is_g_v(int8_t i, t_varint *v)
{
	if (i == 3)
	{
		if (v->sign != -1 && v->sign != 1
			&& ft_dprintf(2, V_ERR, KRED, KNRM))
			return (true);
		return (false);
	}
	if (v->len == 1)
	{
		if ((v->sign == 1 || v->sign == -1)
			&& v->x[0] == i && (v->sign = 1))
			return (true);
		if (v->sign == 1 && v->x[0] == i)
			return (true);
	}
	return (false);
}

/*
**	v_len check for the len of v and return it.
**	depending on msc (Most Significant Chunk) we can limit the range of the check
**	if we need full viewing on v data we set msc to V_MAX_LEN (cost more computation time)
*/

void			v_len(t_varint *v, int16_t msc)
{
	int16_t		i;

	i = msc;
	while (--i > 0)
		if (v->x[i])
			break ;
	v->len = i + 1;
}

/*
** load len uint8_t from uint8_t *src in a varint variable n and return it
*/

t_varint		v_init(char sign, uint8_t *src, int16_t len)
{
	t_varint		v;
	int16_t		i;

	if (sign != -1 && sign != 1)
		return (g_v[3]);
	if ((len <= 0 || len > V_MAX_LEN)
		&& ft_dprintf(2, V_ERR_LEN_0, KRED, KNRM))
		return (g_v[3]);
	v = g_v[0];
	v.sign = sign;
	i = -1;
	while (++i < len)
		v.x[i] = src[i];
	v_len(&v, len);
	is_g_v(0, &v);
	return (v);
}

/*
**	v_sort:
**
**	if sign == NULL
**		put bigger in a and lower in b (with regard on their signs)
**	else 
**		put bigger absolute in a and lower absolute in b
**		save the sign of the bigger absolute in sign[0] (respectively sign[1] for the lower absolute)
**		and finally turn a->sign and b->sign to one
**
**	return -1 for error, 1 if switch occured, 0 if not
*/


uint8_t			v_sort(t_varint *a, t_varint *b, int8_t *sign)
{
	t_varint	tmp;
	int8_t	tmp_sign;

	if (sign)
	{
		sign[0] = a->sign;
		sign[1] = b->sign;
		a->sign = 1;
		b->sign = 1;
	}	
	if (v_cmp(a, "-lt", b, false))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
		if (sign)
		{
			tmp_sign = sign[0];
			sign[0] = sign[1];
			sign[1] = tmp_sign;
		}
		return (1);
	}
	return (0);
}

/*
**	ft_dprintf(2, "%s|%hhd|%hd:\n", name, v->sign, v->len);
*/

void			v_print(int fd, char *name, t_varint *v, bool check)
{
	int8_t		k;
	int16_t		i;

	ft_dprintf(fd, "%s:\n", name);
	if (check && !v_check(v, NULL, NULL, "print"))
		return ;
	if (v->x[v->len - 1] & 0x80)
		ft_dprintf(fd, "    00:");
	k = (v->x[v->len - 1] & 0x80) ? 1 : 0;
	i = v->len;
	while (--i >= 0)
	{
			if (k == 0)
				ft_dprintf(fd, "    ");
			ft_dprintf(fd, "%02x", v->x[i]);
			if (i == 0)
				break;
			ft_dprintf(fd, ":");
			k++;
			if ((k %= 15) == 0)
				ft_dprintf(fd, "\n");
	}
	ft_dprintf(fd, "\n");
}
