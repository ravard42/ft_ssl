#include "ft_ssl.h"


static char *v_name[] = {"modulus",
						"publicExponent", "privateExponent",
						"prime1", "prime2", "exponent1", "exponent2",
						"coefficient"};


void						text(int8_t nb_v, t_parse *p)
{
	int8_t	i;

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

void					print_opt(int8_t nb_v, t_parse *p)
{
	int8_t					mod_id;

	if (p->a.o[9])
		text(nb_v, p);
	if (p->a.o[10] && ft_dprintf(1, "Modulus="))
	{
		mod_id = (nb_v == 2) ? 0 : 1;
		ft_putrhex(p->a.rsak[mod_id].x, p->a.rsak[mod_id].len, 3);
	}	
	
}

int						rsa(t_parse *p)
{
	int		nb_v;

	if (!(nb_v = read_rsak(p)))
		return (0);
	print_opt(nb_v, p);
	if (!p->a.o[11])
		write_rsak(p, nb_v);
	return (0);
}
