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

	prng(rand_a, n.len, rng);
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
	if ((is_g_v(1, &r)
		|| v_cmp(&r, "-eq", &n_min_1, false))
		&& ft_dprintf(2, "+"))
		return (false);
	i = g_v[1];
	while (v_cmp(&i, "-lt", &s, false))
	{
		r = v_expmod(r, g_v[2], n, false);
		if (v_cmp(&r, "-eq", &n_min_1, false)
			&& ft_dprintf(2, "+"))
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

static bool			prob_prim_test(t_varint *n, t_rng *rng)
{
	t_varint	n_min_1;
	t_varint	s[2];
	t_varint	d;
	int8_t		nb_a;

	if (!sieve(n))
		return (false);
	n_min_1 = v_sub(*n, g_v[1], false);
	s[0] = g_v[1];
	s[1] = g_v[2];
	d = v_mod(n_min_1, s[1], true, false);
	while (is_g_v(0, &d) && v_inc(s, false))
	{
		s[1] = v_left_shift(s[1], false);
		d = v_mod(n_min_1, s[1], true, false);
	}
	v_dec(s, false);
	s[1] = v_right_shift(s[1], false);
	d = v_div(n_min_1, s[1], false);
	nb_a = NB_MIL_RAB;
	while (nb_a--)
		if (miller_witness(*n, s[0], d, rng))
			return (false);
	return (true);
}

/*
** about the process of generating random nb-bit prime candidat in varint:
** 1] we load a full random uint8_t varint v s.t v.len = len 
**		where len is the lower len that can contain nb-bit
**	2]	we make it odd turning LSB to one
**	3] we apply a bitmask on the head of v
**		which set bits of index nb - 1 and nb - 2 to 1 and 0 respectively and all uppers to 0
**
**	NB : 64 <= mod_nb <= 4096
**		  so 32 <= nb <= 2048
**		  and v >= 0x80000001 (remark: v is bigger than all g_prime numbers)
**		  we set bit of index nb - 2 to 0 cause we don't want sieve to return an nb + 1 bit lenght number 
*/

void				v_mask(t_varint *v, int16_t nb)
{
	int8_t		upper_msb_id;
	uint8_t		mask;

	v->x[0] |= 0x1;
	upper_msb_id = (nb - 1) % V_BIT_LEN;
	if (upper_msb_id == 0)
	{
		v->x[v->len - 1] = 1;
		v->x[v->len - 2] &= 0x7f;
	}
	else
	{
		v->x[v->len - 1] &= (0xff >> (7 - upper_msb_id));
		mask = 1 << upper_msb_id;
		v->x[v->len - 1] |= mask;
		mask >>= 1;
		mask = ~mask; 
		v->x[v->len - 1] &= mask;
	}
}

t_varint			find_prime(int16_t nb, int16_t len, t_rng *rng)
{
	uint8_t		rand_v[len];
	t_varint		v;
	bool			is_prime;

	if (len * 2 > V_MAX_LEN
		&& ft_dprintf(2, "%soverflow in prob_prim_test, increase V_MAX_LEN%s\n", KRED, KNRM))
		return (g_v[3]);
	is_prime = false;
	while (!is_prime)
	{
		if (!prng(rand_v, len, rng))
			return (g_v[3]);
		v = v_init(1, rand_v, len);
		v_mask(&v, nb);
		is_prime = prob_prim_test(&v, rng);
	}
	return (v);
}
