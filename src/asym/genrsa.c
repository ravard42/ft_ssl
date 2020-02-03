#include "ft_ssl.h"

static void				v_print_hex(t_varint *v)
{
	for(int i = v->len - 1; i != 0; i--)
		ft_printf("%s%016lx%s", KGRN, v->x[i], KNRM);
	ft_printf("%s%016lx\n%s", KGRN, v->x[0], KNRM);
}

/*
** rsa key order : version, n, e, d, p, q, dp, dq, qinv
*/

/*
**	1 + (nb - 1) / (V_BIT_LEN) is the lower number of random V_TYPE needed
** to construct all kind of nb-bit number in a varint variable
*/

int						genrsa(t_parse *p)
{
//	ft_printf("input rand file for PRNG seeding : %s\n", p->in_file);
//	ft_printf("output file : %s\n", p->out_file);

//	bool			is_set[2];
	int16_t		nb[2];
	t_varint		prime[2];
//	t_varint		tmp;

//	ft_dprintf(2, "Generating RSA private key, %hd bit long modulus (2 primes)\n", p->a.mod_nb);
//	is_set[0] = false;
//	is_set[1] = false;
	nb[0] = p->a.mod_nb - p->a.mod_nb / 2;
//	nb[1] = p->a.mod_nb / 2;
////	ft_printf("nb = (%d, %d)\nlen = (%d, %d)\n", nb[0], nb[1], 1 + (nb[0] - 1) / V_BIT_LEN, 1 + (nb[1] - 1)/ V_BIT_LEN);
//
//	while (!is_set[0])
//	{
//		prime[0] = find_prime(nb[0], 1 + (nb[0] - 1) / V_BIT_LEN, &p->rng);
//		if (is_g_v(3, prime))
//			return (0);
//		tmp = v_gcd(g_v[4], prime[0]);
//		if (!is_g_v(1, &tmp))
//			ft_dprintf(2, "*");
//		else if ((is_set[0] = true))
//			ft_dprintf(2, "\n");
//	}
//	while (!is_set[1])
//	{
//		prime[1] = find_prime(nb[1], 1 + (nb[1] - 1) / V_BIT_LEN, &p->rng);
//		if (is_g_v(3, prime + 1))
//			return (0);
//		tmp = v_gcd(g_v[4], prime[1]);
//		if (!is_g_v(1, &tmp)
//			|| v_cmp(prime, "-eq", prime + 1, false))
//			ft_dprintf(2, "*");
//		else if ((is_set[1] = true))
//			ft_dprintf(2, "\n");
//	}
//	ft_dprintf(2, "e is 65537 (0x010001)\n");
//	v_print_hex(prime);
//	v_print_hex(prime + 1);

	for (int i = 0; i < 2; i++)
	{
		prime[0] = find_prime(nb[0], 1 + (nb[0] - 1) / V_BIT_LEN, &p->rng);
		v_print_hex(prime);
	}
	return (0);
}
