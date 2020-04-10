#include "libft.h"
/*
**	ft_dprintf(2, "%s|%hhd|%hd:\n", name, v->sign, v->len);
*/

void			v_print(int fd, char *name, t_varint *v)
{
	int8_t		k;
	int16_t		i;

	if (!v_check(v, NULL, NULL, "print"))
		return ;
	ft_dprintf(fd, "%s:\n", name);
	if (v->x[v->len - 1] & 0x80)
		ft_dprintf(fd, "    00:");
	k = (v->x[v->len - 1] & 0x80) ? 1 : 0;
	i = v->len;
	while (--i >= 0)
	{
			if (k == 0)
				ft_dprintf(fd, "    ");
			ft_dprintf(fd, "%02x", v->x[i]);
			if (i == 0)
				break;
			ft_dprintf(fd, ":");
			k++;
			if ((k %= 15) == 0)
				ft_dprintf(fd, "\n");
	}
	ft_dprintf(fd, "\n");
}

static void		v_dumpline(int fd, t_varint *v, int16_t k, int8_t len)
{
	char			c[17];
	int8_t		i;

	ft_memset(c, '.', len);
	c[len] = 0;
	i = -1;
	while (++i < len)
	{
		if (i != 7)
			ft_dprintf(fd, "%02x ", v->x[k * 16 + i]);
		else
			ft_dprintf(fd, "%02x-", v->x[k * 16 + i]);
		if (v->x[k * 16 + i] >= 0x20 && v->x[k * 16 + i] <= 0x7e)
			c[i] = v->x[k * 16 + i];
	}
	while (i++ < 16)
			ft_dprintf(fd, "   ");
	ft_dprintf(fd, "  %s", c);
	ft_dprintf(fd, "\n");
}

void				v_hexdump(int fd, t_varint *v)
{
	short			addr;
	int16_t		k;

	if (!v_check(v, NULL, NULL, "hexdump"))
		return ;
	addr = 0;
	k = -1;
	while (++k < v->len / 16)
	{
			ft_dprintf(1, "%04hx - ", addr);
			v_dumpline(fd, v, k, 16);
			addr += 16;
	}
	if (v->len % 16)
	{
		ft_dprintf(1, "%04hx - ", addr);
		v_dumpline(fd, v, k, v->len % 16);
	}
}
