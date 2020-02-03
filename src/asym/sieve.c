#include "ft_ssl.h"

static uint16_t	*build_sieve(t_varint *n)
{
	short 	i;
	uint16_t	*remainder;
	t_varint	tmp;

	remainder = (uint16_t *)malloc(sizeof(uint16_t) * G_PRIME_LEN);
	tmp = g_v[0];
	i = -1;
	while (++i < G_PRIME_LEN)
	{
		tmp.x[0] = g_prime[i];
		tmp = v_mod(*n, tmp, true, false);
		remainder[i] = tmp.x[0];
	}
	return (remainder);
}

bool					sieve(t_varint *n)
{
	uint16_t		*remainder;
	uint16_t		delta_n;
	short			i;

	remainder = build_sieve(n);
	delta_n = 0;
	while (delta_n <= 0xffff - g_prime[G_PRIME_LEN - 1])
	{
		i = -1;
		while (++i < G_PRIME_LEN)
			if ((delta_n + remainder[i]) % g_prime[i] == 0)
				break;
		if (i == G_PRIME_LEN)
		{
			free(remainder);
			return (true);
		}
		delta_n += 2;
		v_inc(n);
		v_inc(n);
	}
	free(remainder);
	ft_printf("*");
	return (false);
}
