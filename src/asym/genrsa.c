#include "ft_ssl.h"

/*
** rsa key order : version, n, e, d, p, q, dp, dq, qinv
*/



int						genrsa(t_parse *p)
{
	ft_printf("%sCOUCOU GENRSA%s\n", KCYN, KNRM);
	ft_printf("input rand file for PRNG seeding : %s\n", p->in_file);
	ft_printf("output file : %s\n", p->out_file);
	ft_printf("numbits = %d\n", p->a.m_nb);

	t_varint	prime;
	while (1)
	{
		prime = find_prime(64, p);
		for(int i = prime.len - 1; i != 0; i--)
			ft_printf("%s%016lx%s", KGRN, prime.x[i], KNRM);
		ft_printf("%s%016lx\n%s", KGRN, prime.x[0], KNRM);
	}
	return (0);
}
