#include "ft_ssl.h"

static void				hexdump(t_read *r)
{
	ft_puthex(1, r->msg, r->len, 5);
}

int						rsautl(t_parse *p)
{
	int		nb_v;
	uint8_t	tmp_o[13];

	ft_memcpy(&tmp_o, p->a.o, 13);
	ft_memset((char *)p->a.o, 0, 13);
	p->a.o[7] = tmp_o[3];
	if (!(nb_v = read_rsak(p)))
		return (0);
	ft_memcpy(p->a.o, &tmp_o, 13);


	hexdump(&p->a.data);
	for (int i = 0; i < 9; i++)
		v_print(1, "youp", p->a.rsak + i);

	return (0);
}
