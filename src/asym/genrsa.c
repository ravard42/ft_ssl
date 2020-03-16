#include "ft_ssl.h"

static t_varint				set_rsa_prime(int16_t nb, t_rng *rng)
{
	t_varint		tmp;
	t_varint		ret;
	
	while (true)
	{
		ret = find_prime(nb, 1 + (nb - 1) / V_BIT_LEN, rng);
		if (is_g_v(3, &ret)
			&& ft_dprintf(2, "%sprogram leaving ...\n%s", KRED, KNRM))
			exit(0);
		tmp = v_gcd(g_f4, v_sub(ret, g_v[1], false), false);
		if (!is_g_v(1, &tmp) && ft_dprintf(2, "*"))
			continue ;
		ft_dprintf(2, "\n");
		break ;
	}
	return (ret);
}

/*
**	1 + (nb - 1) / (V_BIT_LEN) is the lower number of random uint8_t needed
** to construct all kind of nb-bit number in a varint variable
*/

int						genrsa(t_parse *p)
{
	t_varint		p_min_1;
	t_varint		q_min_1;

	p->a.rsak[0] = g_v[0];
	ft_dprintf(2, GENRSA_RUNNING, p->a.mod_nb);
	p->a.rsak[4] = set_rsa_prime(p->a.mod_nb - p->a.mod_nb / 2 + 1, &p->rng);
	p_min_1 = v_sub(p->a.rsak[4], g_v[1], false);
	p->a.rsak[5] = set_rsa_prime(p->a.mod_nb / 2, &p->rng);
	while (v_cmp(p->a.rsak + 4, "-eq", p->a.rsak + 5, false))	
		p->a.rsak[5] = set_rsa_prime(p->a.mod_nb / 2, &p->rng);
	q_min_1 = v_sub(p->a.rsak[5], g_v[1], false);
	p->a.rsak[1] = v_mul(p->a.rsak[4], p->a.rsak[5], false);
	ft_dprintf(2, "e is 65537 (0x010001)\n");
	p->a.rsak[2] = g_f4;
	p->a.rsak[3] = v_inv(g_f4, v_mul(p_min_1, q_min_1, false), false);
	p->a.rsak[6] = v_mod(p->a.rsak[3], p_min_1, true, false);
	p->a.rsak[7] = v_mod(p->a.rsak[3], q_min_1, true, false);
	p->a.rsak[8] = v_inv(p->a.rsak[5], p->a.rsak[4], false);
	return (write_rsak(p, 9));
}
