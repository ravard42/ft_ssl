#include "ft_ssl.h"

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
	data = g_v[0];
	ft_memcpy(data.x, p->a.data.msg, p->a.data.len);
	data.len = p->a.data.len;	
	v_hexdump(1, &data);

	return (0);
}
