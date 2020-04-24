#include "ft_ssl.h"

/*
** about the process of generating random nb-bit prime candidat in varint:
** 1] we load a full random uint8_t varint v s.t v.len = len 
**		where len is the lower len that can contain nb-bit
**	2]	we make it odd turning LSB to one
**	3] we apply a bitmask on the head of v
**		which set bits of index nb-1, nb-2, nb-3 to 1, 0, 0 respectively and all uppers to 0
**
**	NB : 64 <= mod_nb <= 4096
**		  so 32 <= nb <= 2048
**		  and v >= 0x80000001 (remark: v is bigger than all g_prime numbers)
**		  we set bit of index nb-2 and nb-3 to 0 cause
**				1] we don't want sieve to return an nb+1 bit lenght number (nb-2 == 0) 
**				2] modulus has always valid length (nb-3=0)
*/

static void				v_mask(t_varint *v, int16_t nb)
{
	int8_t		upper_msb_id;
	uint8_t		mask;

	v->x[0] |= 0x1;
	upper_msb_id = (nb - 1) % V_BIT_LEN;
	if (upper_msb_id == 0 || upper_msb_id == 1)
	{
		v->x[v->len - 1] = (upper_msb_id == 0) ? 1 : 2;
		v->x[v->len - 2] &= (upper_msb_id == 0 ) ? 0x3f : 0x7f;
	}
	else
	{
		v->x[v->len - 1] |= (1 << upper_msb_id);
		v->x[v->len - 1] <<= (7 - upper_msb_id);
		v->x[v->len - 1] >>= (7 - upper_msb_id);
		mask = 3 << (upper_msb_id - 2);
		v->x[v->len - 1] &= ~mask;
	}
}

static t_varint			find_prime(int16_t nb, int16_t len, t_rng *rng, bool check)
{
	uint8_t		rand_v[len];
	t_varint		v;
	bool			is_prime;

	if (check && len * 2 > V_MAX_LEN
		&& ft_dprintf(2, "%soverflow in prob_prim_test, increase V_MAX_LEN%s\n", KRED, KNRM))
		return (g_v[3]);
	is_prime = false;
	while (!is_prime)
	{
		if (!prng(rand_v, len, rng, 2))
			return (g_v[3]);
		v = v_init(1, rand_v, len);
		v_mask(&v, nb);
		if (!sieve(&v))
			continue;
		is_prime = prob_prime_test(&v, rng, true);
	}
	return (v);
}

/*
**	1 + (nb - 1) / (V_BIT_LEN) is the lower number of random uint8_t needed
** to construct all kind of nb-bit number in a varint variable
*/

static t_varint				set_rsa_prime(int16_t nb, t_rng *rng)
{
	t_varint		tmp;
	t_varint		ret;
	
	while (true)
	{
		ret = find_prime(nb, 1 + (nb - 1) / V_BIT_LEN, rng, false);
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

int						genrsa(t_parse *p)
{
	int16_t		verif_len;
	t_varint		p_min_1;
	t_varint		q_min_1;

	verif_len = p->a.mod_nb / 8;
	verif_len += (p->a.mod_nb % 64) ? (8 - verif_len % 8) + 8 : 8;
	if (verif_len > V_MAX_LEN
		&& ft_dprintf(2, ERR_GENRSA_LEN, KRED, verif_len, KNRM))
		return (-1);
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
