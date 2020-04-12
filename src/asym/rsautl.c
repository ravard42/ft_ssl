#include "ft_ssl.h"

static bool				rsa_pad(t_varint *data, t_parse *p, int nb_v)
{
	t_varint		*modulus;

	modulus = p->a.rsak + nb_v % 2;
	if (p->a.data.len + 11 > modulus->len
		&& ft_dprintf(2, "data too large for key size\n", KRED, KNRM))
		return (false);
	*data = g_v[0];
	data->x[1] = 0x02;
	if (!prng(data->x + 2, modulus->len - p->a.data.len - 3, &p->rng, 1))
		return (false);
	
	return (true);	
}

int						rsautl(t_parse *p)
{
	int		nb_v;
	uint8_t	tmp_o[13];
	t_varint	data;

	ft_memcpy(&tmp_o, p->a.o, 13);
	ft_memset((char *)p->a.o, 0, 13);
	p->a.o[7] = tmp_o[3];
	if (!(nb_v = read_rsak(p)))
		return (0);
	ft_memcpy(p->a.o, &tmp_o, 13);

	//FINISHING STRAIGHT LINE

	//HEXDUMP TEST
	//	data = g_v[0];
	//	ft_memcpy(data.x, p->a.data.msg, p->a.data.len);
	//	data.len = p->a.data.len;	
	//	v_hexdump(1, &data);
	
	//ENC (nb_v == 2 || nb_v == 9) ==> 	nb_v % 2 == 0 if -inkey is pubkey
	//												nb_v % 2 == 1 if -inkey is prikey
	if (p->a.o[4])
	{
		if (!rsa_pad(&data, p, nb_v)) //need p->a.data for data + p->a.rsak for modulus size in byte + nb_v for offset
			return (0);
		//data = v_expmod(data, p->rsak[1 + nb_v % 2], true, false)
		
	}
	
	//DEC
//	else if (p->a.o[5]) 
//	
//	else
//		ft_dprintf(2, "%srsautl command doesn't know what to do%s\n", KRED, KNRM);
	return (0);
}
