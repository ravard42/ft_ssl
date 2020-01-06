#include "ft_rsa.h"

t_varint					v_rand_n(int fd, LEN_TYPE len)
{
	TYPE			rand_n[len];
	LEN_TYPE		i;
	t_varint		n;

	i = -1;
	while (++i < len)
		rand_n[i] = ft_rand(fd, 0, 0);
	n = v_init(rand_n, len);
	return (n);
}

static t_varint		v_rand_a(int fd, t_varint n)
{
	TYPE				rand_a[n.len];
	LEN_TYPE			i;
	t_varint			a;

	if (n.len == 1)
		rand_a[0] = ft_rand(fd, 2, n.x[0] - 1);
	else
	{
		rand_a[0] = ft_rand(fd, 2, SUP);
		i = 0;
		while (++i < n.len - 1)
			rand_a[i] = ft_rand(fd, 0, 0);
		rand_a[n.len - 1] = ft_rand(fd, 0, n.x[n.len - 1] - 1);
	}
	a = v_init(rand_a, n.len);
	return (a);
}

static int	miller_witness(int fd, t_varint n, t_varint s, t_varint d)
{
	t_varint	n_min_1;
	t_varint	a;
	t_varint r;
	t_varint	i;

	n_min_1 = v_dec(n);
	a = v_rand_a(fd, n);	
	r = v_expmod(a, d, n);
	if (v_cmp(r, "-eq", g_v_1)
		|| v_cmp(r, "-eq", n_min_1))
		return false;
	i = g_v_1;
	while (v_cmp(i, "-lt", s))
	{
		r = v_expmod(r, g_v_2, n);
		if (v_cmp(r, "-eq", n_min_1))
			return (false);
		i = v_inc(i);
	}
	return (true);
}

static bool	first_prime_composite(t_varint n)
{
	t_varint	p;
	int		i;

	if (n.len != 1)
	{
		i = -1;
		while (++i < 2048)
		{
			p.x[0] = g_prime[i];
			p.x[1] = (SUP == 0xff) ? *((uint8_t *)(g_prime + i) + 1) : 0;
			p.len = (p.x[1]) ? 2 : 1;
			if(v_cmp(v_mod(n, p), "-eq", g_v_0))
				return true;
		}
		return (false);
	}
	while (++i < 2048)
		if (n.x[0] % g_prime[i] == 0)
			return true;
	return (false);
}

bool			prob_prim_test(int fd, t_varint n)
{
	int8_t	nb_a;
	t_varint	n_min_1;
	t_varint s;
	t_varint d;

//	v_print(&n, "n", -1, KYEL);
	if (first_prime_composite(n) || v_cmp(n, "-le", g_v_2))
		return (false);
//	v_print(&n, "n", -1, KRED);
	nb_a = 1;
	n_min_1 = v_dec(n);
	s = g_v_1;
	while (v_cmp(v_mod(n_min_1, v_exp(g_v_2, s)), "-eq", g_v_0))
		s = v_inc(s);
	s = v_dec(s);
	d = v_div(n_min_1, v_exp(g_v_2, s));
	while (nb_a--)
		if (miller_witness(fd, n, s, d))
			return (false);
	return (true);
}
