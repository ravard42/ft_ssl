#include "ft_ssl.h"


static char *v_name[] = {"modulus",
						"publicExponent", "privateExponent",
						"prime1", "prime2", "exponent1", "exponent2",
						"coefficient"};


void						text(t_parse *p, int nb_v)
{
	int	i;

	if (nb_v == 2)
	{
		ft_dprintf(1, "RSA Public-Key: (%hd bit)\n", v_msb_id(p->a.rsak) + 1);
		v_print(1, "Modulus", p->a.rsak);
		ft_dprintf(1, "Exponent: 65537 (0x10001)\n");
	}
	else if (nb_v == 9)
	{
		ft_dprintf(1, "RSA Private-Key: (%hd bit, 2 primes)\n", v_msb_id(p->a.rsak + 1) + 1);
		i = -1;
		while (++i < 8)
		{
			if (i == 1)
				ft_dprintf(1, "publicExponent: 65537 (0x10001)\n");
			else
				v_print(1, v_name[i], p->a.rsak + i + 1);
		}
	}
}

void					print_opt(t_parse *p, int nb_v)
{
	int					mod_id;

	if (p->a.o[9])
		text(p, nb_v);
	if (p->a.o[10] && ft_dprintf(1, "Modulus="))
	{
		mod_id = (nb_v == 2) ? 0 : 1;
		ft_putrhex(1, p->a.rsak[mod_id].x, p->a.rsak[mod_id].len, 3);
	}	
}

// check len of input key to prevent overflow in check_opt
static void			check_opt(int *err, t_parse *p, int nb_v)
{
	t_varint		tmp[7];

	if (nb_v != 9 && (*err += ft_dprintf(1, R_CHECK_0, KYEL, KNRM)))
		return ;
	if (!prob_prime_test(p->a.rsak + 4, &p->rng, false))
		*err += ft_dprintf(1, R_CHECK_1, KRED, KNRM);
	if (!prob_prime_test(p->a.rsak + 5, &p->rng, false))
		*err += ft_dprintf(1, R_CHECK_2, KRED, KNRM);
	tmp[0] = v_sub(p->a.rsak[4], g_v[1], false);
	tmp[1] = v_sub(p->a.rsak[5], g_v[1], false);
	tmp[2] = v_mul(tmp[0], tmp[1], false);
	tmp[3] = v_mod(v_mul(g_f4, p->a.rsak[3], false), tmp[2], true, false);
	if (!is_g_v(1, tmp + 3))
		*err += ft_dprintf(1, R_CHECK_3, KRED, KNRM);
	tmp[4] = v_mod(p->a.rsak[3], tmp[0], true, false);
	if (!v_cmp(p->a.rsak + 6, "-eq", tmp + 4, false))
		*err += ft_dprintf(1, R_CHECK_4, KRED, KNRM);
	tmp[5] = v_mod(p->a.rsak[3], tmp[1], true, false);
	if (!v_cmp(p->a.rsak + 7, "-eq", tmp + 5, false))
		*err += ft_dprintf(1, R_CHECK_5, KRED, KNRM);
	tmp[6] = v_mod(v_mul(p->a.rsak[5], p->a.rsak[8], false), p->a.rsak[4], true, false);
	if (!is_g_v(1, tmp + 6))
		*err += ft_dprintf(1, R_CHECK_6, KRED, KNRM);
}

/*
**	o[9] : 1 for -text, else 0
**	o[10] : 1 for -modulus, else 0
**	o[11] : 1 for -noout, else 0
**	o[12] : 1 for -check, else 0
*/

int						rsa(t_parse *p)
{
	int		nb_v;
	int		err;

	if (!(nb_v = read_rsak(p)))
		return (0);
	print_opt(p, nb_v);
	if (p->a.o[12])
	{
		err = 0;
		check_opt(&err, p, nb_v);
		if (err == 0)
			ft_dprintf(1, CHECK_SUCCESS, KGRN, KNRM);
	}
	if (!p->a.o[11])
		write_rsak(p, nb_v);
	return (0);
}
