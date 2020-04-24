#include "libft.h"

static void		dumpline(int fd, uint8_t *p, int16_t k, int8_t len)
{
	char			c[17];
	int8_t		i;

	ft_memset(c, '.', len);
	c[len] = 0;
	i = -1;
	while (++i < len)
	{
		if (i != 7)
			ft_dprintf(fd, "%02x ", p[k * 16 + i]);
		else
			ft_dprintf(fd, "%02x-", p[k * 16 + i]);
		if (p[k * 16 + i] >= 0x20 && p[k * 16 + i] <= 0x7e)
			c[i] = p[k * 16 + i];
	}
	while (i++ < 16)
			ft_dprintf(fd, "   ");
	ft_dprintf(fd, "  %s", c);
	ft_dprintf(fd, "\n");
}

void				ft_hexdump(int fd, void *p, size_t len)
{
	uint8_t		*ui8p;
	size_t		addr;
	size_t		k;

	ui8p = (uint8_t *)p;
	addr = 0;
	k = -1;
	while (++k < len / 16)
	{
			ft_dprintf(fd, "%04hx - ", addr);
			dumpline(fd, ui8p, k, 16);
			addr += 16;
	}
	if (len % 16)
	{
		ft_dprintf(fd, "%04hx - ", addr);
		dumpline(fd, ui8p, k, len % 16);
	}
}
