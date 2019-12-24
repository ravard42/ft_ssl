#include "libft.h"

/*
** about crt[8]
**
**	index 		data
**				
**		0			cp
**		1			dp
**	 	2			cq
**	 	3			dq
**	 	4			qinv
**	 	5			m1
**	 	6			m2
**	 	7			h
*/

t_varint		v_crt(t_varint v, t_varint e, t_varint p, t_varint q)
{
	int8_t						j;
	t_varint						n;
	t_varint						crt[8];

	n = v_mul(p, q);
	if ((j = v_check(v, e, n, "expmod")) != -1)
		return (g_v[j]);
	crt[0] = v_mod(v, p, true);
	crt[1] = v_mod(e, v_dec(p), true);
	crt[2] = v_mod(v, q, true);
	crt[3] = v_mod(e, v_dec(q), true);
	crt[4] = v_inv(q, p);

	crt[5] = v_expmod(crt[0], crt[1], p, true);
	crt[6] = v_expmod(crt[2], crt[3], q, true);
	crt[7] = v_mod(v_mul(crt[4], v_sub(crt[5], crt[6])), p, true);

	return (v_mod(v_add(crt[6], v_mul(crt[7], q)), n, true));
}
