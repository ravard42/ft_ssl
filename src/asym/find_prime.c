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
**	at the end of each loop we need an lvalue which contained n mod(p)
**	endeed is_g_v expect a memory adrress and v_mod return an rvalue
**	cause we don't need p anymore in this round we use it as this lvalue
**	(no relation with a prime number until the next loop begins)
*/

static bool			first_prime_composite(t_varint n)
{
	t_varint	p;
	int			i;

	i = -1;
	while (++i < 2048)
	{
		p = g_v[0];
		p.x[0] = g_prime[i];
		if (V_SUP == 0xff && V_MAX_LEN > 1)
		{
			p.x[1] = *((uint8_t *)(g_prime + i) + 1);
			p.len = (p.x[1]) ? 2 : 1;
		}
		if (v_cmp(&n, "-eq", &p, false))
			return (false);
		p = v_mod(n, p, true, false);
		if (is_g_v(0, &p))
			return (true);
	}
	return (false);
}

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
	V_TYPE				rand_a[n.len];
	t_varint			a;

	prng(rand_a, n.len * V_LEN, rng);
	if (n.len == 1)
		rand_a[0] = ft_range(rand_a[0], 2, n.x[0] - 1);
	else
	{
		rand_a[0] = ft_range(rand_a[0], 2, V_SUP);
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
		return (false);
	i = g_v[1];
	while (v_cmp(&i, "-lt", &s, false))
	{
		r = v_expmod(r, g_v[2], n, false);
		if (v_cmp(&r, "-eq", &n_min_1, false))
			return (false);
		v_inc(&i);
	}
	return (true);
}

/*
**	n_min_1 = 2^s * d  (with d % 2 == 0)
**
**	NB :in first place we use d as an lvalue
**		to store intermediate results to compute s
*/

static bool			prob_prim_test(t_varint n, t_rng *rng)
{
	int8_t		nb_a;
	t_varint	n_min_1;
	t_varint	s;
	t_varint	d;

	if (v_cmp(&n, "-le", &g_v[2], false)
		|| first_prime_composite(n))
		return (false);
	nb_a = 1;
	n_min_1 = v_sub(n, g_v[1], false);
	s = g_v[1];
	d = v_mod(n_min_1, v_exp(g_v[2], s), true, false);
	while (is_g_v(0, &d) && v_inc(&s))
		d = v_mod(n_min_1, v_exp(g_v[2], s), true, false);
	v_dec(&s);
	d = v_div(n_min_1, v_exp(g_v[2], s), false);
	while (nb_a--)
		if (miller_witness(n, s, d, rng))
			return (false);
	return (true);
}

/*
**	1 + (p_nb - 1) / 8 is the number of random byte data needed to construct a nb-bit prime number
**	reminder : mod_nb >= 128 so p_nb >= 64 
**
*/

t_varint			find_prime(int16_t p_nb, t_rng *rng)
{
	V_TYPE		rand_n[1 + (p_nb - 1) / 8];
	t_varint	n;
	bool		is_prime;
//	int16_t		upper_nb;
//	uint64_t	mask;

	if ((1 + (p_nb - 1) / 8) * 2 > V_MAX_LEN * V_LEN
		&& ft_dprintf(2, "%soverflow in prob_prim_test, increase V_MAX_LEN or V_TYPE size%s\n", KRED, KNRM))
		return (g_v[3]);
	is_prime = false;
	while (!is_prime)
	{
		prng(rand_n, 1 + (p_nb - 1) / 8, rng);
		n = v_init(1, rand_n, (1 + (p_nb - 1) / 8) / V_LEN);
//		v_print(&n, "n", -2, KYEL);
//		n = v_rand(nb / 64 + 1, false);
		n.x[0] += (n.x[0] % 2 == 0) ? 1 : 0;
//		upper_nb = nb % 64;
//		n.x[n.len - 1] <<= (64 - upper_nb);
//		n.x[n.len - 1] >>= (64 - upper_nb);
//		mask = 1 << upper_nb;
//		n.x[n.len - 1] |= mask;
		is_prime = prob_prim_test(n, rng);
	}
	return (n);
}
