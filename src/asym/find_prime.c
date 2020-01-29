#include "ft_ssl.h"

/*
** Miller-Rabin Probabilistic Primality Test
*/

static t_varint		v_rand_a(t_varint n, t_parse *p)
{
	V_TYPE				rand_a[n.len];
//	V_LEN_TYPE			i;
	t_varint				a;

	if (n.len == 1)
		//rand_a[0] = ft_rand(fd, 2, n.x[0] - 1);
		rand_a[0] = ft_range(*(V_TYPE *)prng(rand_a, V_LEN, p), 2, n.x[0] - 1);
	else
	{
//		rand_a[0] = ft_rand(fd, 2, V_SUP);
		prng(rand_a, n.len * V_LEN, p);
		rand_a[0] = ft_range(rand_a[0], 2, V_SUP);
		rand_a[n.len - 1] = ft_range(rand_a[0], 0, n.x[n.len - 1] - 1);
//		i = 0;
//		while (++i < n.len - 1)
//			rand_a[i] = ft_rand(fd, 0, 0);
//		rand_a[n.len - 1] = ft_rand(fd, 0, n.x[n.len - 1] - 1);
	}
	a = v_init(1, rand_a, n.len);
	return (a);
}

static int	miller_witness(t_varint n, t_varint s, t_varint d, t_parse *p)
{
	t_varint	n_min_1;
	t_varint	a;
	t_varint r;
	t_varint	i;

	n_min_1 = v_sub(n, g_v[1], true);
	a = v_rand_a(n, p);	
	r = v_expmod(a, d, n, true);
	if (is_g_v(1, &r)
		|| v_cmp(&r, "-eq", &n_min_1, true))
		return false;
	i = g_v[1];
	while (v_cmp(&i, "-lt", &s, true))
	{
		r = v_expmod(r, g_v[2], n, true);
		if (v_cmp(&r, "-eq", &n_min_1, true))
			return (false);
		v_inc(&i);
	}
	return (true);
}

/*
**	at the end of each loop we need an lvalue which contained n mod(p)
**	endeed is_g_v expect a memory adrress and v_mod return an rvalue
**	cause we don't need p anymore in this round we use it as this lvalue
**	(no relation with a prime number until the next loop begins)
*/

static bool	first_prime_composite(t_varint n)
{
	t_varint	p;
	int		i;

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
		if (v_cmp(&n, "-eq", &p, true))
			return (false);
		p = v_mod(n, p, true, true);
		if(is_g_v(0, &p))
			return true;
	}
	return (false);
}

/*
**	n_min_1 = 2^s * d  (with d % 2 == 0)
**
**	NB :in first place we use d as an lvalue
**		to store intermediate results to compute s
*/

static bool			prob_prim_test(t_varint n, t_parse *p)
{
	int8_t		nb_a;
	t_varint	n_min_1;
	t_varint 	s;
	t_varint 	d;

	if (first_prime_composite(n)
		|| v_cmp(&n, "-le", &g_v[2], true))
		return (false);
	nb_a = 1;
	n_min_1 = v_sub(n, g_v[1], true);
	s = g_v[1];
	d = v_mod(n_min_1, v_exp(g_v[2], s), true, true);
	while (is_g_v(0, &d) && v_inc(&s))
		d = v_mod(n_min_1, v_exp(g_v[2], s), true, true);
	v_dec(&s);
	d = v_div(n_min_1, v_exp(g_v[2], s), true);
	while (nb_a--)
		if (miller_witness(n, s, d, p))
			return (false);
	return (true);
}



t_varint		find_prime(int16_t nb, t_parse *p)
{
	t_varint n;
	bool		is_prime;
	int16_t	upper_nb;
	uint64_t	mask;


	is_prime = false;
	while (!is_prime)
	{	
		n = v_rand(nb / 64 + 1, false);
		n.x[0] += (n.x[0] % 2 == 0) ? 1 : 0;	
		upper_nb = nb % 64;
		n.x[n.len - 1] <<= (64 - upper_nb);
		n.x[n.len - 1] >>= (64 - upper_nb);
		mask = 1 << upper_nb;
		n.x[n.len - 1] |= mask;

		is_prime = prob_prim_test(n, p);
	}
	return (n);	
			
//	if (print_prime)
//	{
//		if (V_BIT_LEN == 8)
//		{
//			for(int i = len - 1; i != 0; i--)
//				ft_printf("%s%02x%s", KGRN, prime.x[i], KNRM);
//			ft_printf("%s%02x%s\n", KGRN, prime.x[0], KNRM);
//		}
//		else if (V_BIT_LEN == 64)	
//		{
//			for(int i = len - 1; i != 0; i--)
//				ft_printf("%s%016lx%s", KGRN, prime.x[i], KNRM);
//			ft_printf("%s%016lx\n%s", KGRN, prime.x[0], KNRM);
//		}
//		else
//			ft_dprintf(2, "bad V_TYPE for printing\n");
//	}
	//return (prime);	
}
