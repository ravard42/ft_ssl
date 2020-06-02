#include "ft_ssl.h"

/*
** pbd:
** cf. parity_bit_drop function in sym/des/core/key_schedule.c
**	we don't care about bits of index (0, 8, 16, 24, 32, 40, 48, 56) 
**	LSb first (Least Significant bit)
*/

static uint64_t		pbd(uint64_t x)
{
	uint8_t	u8_tab[16] = {0x0};
	uint8_t	i;

	*((uint64_t *)u8_tab) = x;
	i = -1;
	while (++i < 8)
		*((uint64_t *)(u8_tab + i)) <<= 1;
	return (*((uint64_t *)u8_tab));
}

/*
** break_des_ecb:
** test all des_ecb possible keys (brute-force attack)
**	from 0x0000000000000002 to 0xfefefefefefefefe jumping all parity_bit
*/

int						break_des_ecb(t_parse *p)
{
	uint64_t		i;
	uint64_t		key;
	int			fd_log;
	uint64_t		tmp_dec;

	if ((fd_log = open("crypta.log", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1
		&& ft_dprintf(2, "%sopen error on crypta log%s\n", KRED, KNRM))
		return (-1);
	ft_dprintf(fd_log, "plaintext_le = %#018lx\n", p->c.p);
	ft_dprintf(fd_log, "ciphertext_le = %#018lx\n", p->c.c);
	i = -1;
	while (++i < 0x0100000000000000)
	{
		key = pbd(i);
		ft_memcpy(p->s.arg[0].x, &key, 8);
		load_sub_k(&p->s, 0);
		tmp_dec = des_block_d(p->c.c, &p->s);
		if (i % 4096 == 0)
			ft_dprintf(fd_log, "(dec_try_le, key_be, plaintext_le) = (%#018lx, %#018lx, %#018lx)\n", tmp_dec, key, p->c.p);
		if (p->c.p == tmp_dec
			&& ft_dprintf(1, "%sYou found the key : %#018lx\n%s", KGRN, key, KNRM))
			return (0);
	}
	ft_dprintf(2, "%swrong (plaintext, ciphertext) des_ecb couple%s\n", KRED, KNRM);
	close(fd_log);
	return (-1);
}
