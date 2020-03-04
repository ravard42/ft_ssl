#include "ft_ssl.h"

static uint16_t	*build_sieve(t_varint *n)
{
	short 	i;
	uint16_t	*mod_tab;
	t_varint	tmp;

	mod_tab = (uint16_t *)malloc(sizeof(uint16_t) * FST_P_NB);
	tmp = g_v[0];
	i = -1;
	while (++i < FST_P_NB)
	{
		ft_memcpy(tmp.x, g_prime + i, 2);
		tmp.len = (tmp.x[1]) ? 2 : 1;
		tmp = v_mod(*n, tmp, true, false);
		ft_memcpy(mod_tab + i, tmp.x, 2);
	}
	return (mod_tab);
}

static bool			sieve_success(t_varint *n, uint16_t *delta_n, uint16_t *mod_tab)
{
	t_varint		v_delta_n;

	free(mod_tab);
	v_delta_n = g_v[0];
	ft_memcpy(v_delta_n.x, delta_n, 2);
	v_delta_n.len = (v_delta_n.x[1]) ? 2 : 1;
	*n =  v_add(*n, v_delta_n, false);
	ft_dprintf(2, ".");
	return (true);
}

bool					sieve(t_varint *n)
{
	uint16_t		*mod_tab;
	uint16_t		delta_n;
	short			i;

	mod_tab = build_sieve(n);
	delta_n = 0;
	while (delta_n != 0xfffe)
	{
		i = -1;
		while (++i < FST_P_NB)
			if ((delta_n + mod_tab[i]) % g_prime[i] == 0)
				break;
		if (i == FST_P_NB)
			return (sieve_success(n, &delta_n, mod_tab));
		delta_n += 2;
	}
	free(mod_tab);
	ft_dprintf(2, "*");
	return (false);
}
