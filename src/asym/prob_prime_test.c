/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_prime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:31:11 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 04:04:12 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Miller-Rabin Probabilistic Primality Test
*/

/*
** we take 2 <= a <= n - 2 (lower than n so n can't divide a)
** we exclude 1 and n - 1 = -1 mod (n)
** cause they are not miller-witnesses for sur
*/

static t_varint		v_rand_a(t_varint n, t_rng *rng)
{
	uint8_t				rand_a[n.len];
	t_varint			a;

	prng(rand_a, n.len, rng, 0);
	if (n.len == 1)
		rand_a[0] = ft_range(rand_a[0], 2, n.x[0] - 1);
	else
	{
		rand_a[0] = ft_range(rand_a[0], 2, 0xff);
		rand_a[n.len - 1] = ft_range(rand_a[n.len - 1], 0, n.x[n.len - 1] - 1);
	}
	a = v_init(1, rand_a, n.len);
	return (a);
}

static int			miller_witness(t_varint n, t_varint s, t_varint d,
		t_rng *rng)
{
	t_varint	a;
	t_varint	r;
	t_varint	n_min_1;
	t_varint	i;

	a = v_rand_a(n, rng);
	r = v_expmod(a, d, n, false);
	n_min_1 = v_sub(n, g_v[1], false);
	if (is_g_v(1, &r)
		|| v_cmp(&r, "-eq", &n_min_1, false))
//		&& ft_dprintf(2, "+"))
		return (false);
	i = g_v[1];
	while (v_cmp(&i, "-lt", &s, false))
	{
		r = v_expmod(r, g_v[2], n, false);
		if (v_cmp(&r, "-eq", &n_min_1, false))
//			&& ft_dprintf(2, "+"))
			return (false);
		v_inc(&i, false);
	}
	return (true);
}

/*
**	n_min_1 = 2^s * d  (with d % 2 == 0)
**
**	NB :in first place we use d as an lvalue
**		to store intermediate results to compute s
*/

static void			init_miller_rabin(t_varint *n, t_varint *s, t_varint *d)
{ 
	t_varint		n_min_1;

	n_min_1 = v_sub(*n, g_v[1], false);
	s[0] = g_v[1];
	s[1] = g_v[2];
	*d = v_mod(n_min_1, s[1], true, false);
	while (is_g_v(0, d) && v_inc(s, false))
	{
		s[1] = v_left_shift(s[1], false);
		*d = v_mod(n_min_1, s[1], true, false);
	}
	v_dec(s, false);
	s[1] = v_right_shift(s[1], false);
	*d = v_div(n_min_1, s[1], false);
}


bool					prob_prime_test(t_varint *n, t_rng *rng, bool progress_bar)
{
	t_varint	s[2];
	t_varint	d;
	int8_t		nb_a;

	init_miller_rabin(n, s, &d);
	nb_a = NB_MIL_RAB;
	while (nb_a--)
	{
		if (miller_witness(*n, s[0], d, rng))
			return (false);
		else if (progress_bar)
			ft_dprintf(2, "+");
	}
	return (true);
}

