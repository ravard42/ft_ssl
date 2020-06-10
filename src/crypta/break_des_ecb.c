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

static bool				is_key(t_parse *p, uint64_t key, int fd_log, uint64_t log_tic)
{
		uint64_t		dec_try;
		
		ft_memcpy(p->s.arg[0].x, &key, 8);
		load_sub_k(&p->s, 0);
		dec_try = des_block_d(p->c.c, &p->s);
		if (key % log_tic == 0)
			ft_dprintf(fd_log, g_ssl_str[CRYPTA_LOG], dec_try, key, p->c.p);
		if (p->c.p == dec_try)
		{
			ft_dprintf(fd_log, "\n");
			ft_dprintf(fd_log, g_ssl_str[CRYPTA_LOG], dec_try, key, p->c.p);
			ft_dprintf(fd_log, "\nYou found the key : %#018lx\n", key);
			return (true);
		}
		return (false);
}

/*
** break_des_ecb:
** test all des_ecb possible keys (brute-force attack)
**	from 0x0000000000000002 to 0xfefefefefefefefe jumping all parity_bit
**
** about log_tic
**	to not have logs slowing down abusively the algo we don't log all tests
**	e-g:
**	logging just keys verifing key % ft_power(2, n) == 0 will log keys
**	having 0 on their n first lsb
**	remark: if n is in set {0, 8, 16, 24, 32, 40, 48, 56} it's equivalent
**	to choose n + 1 as bits in this set are dropped from the key possibilities
**	and always set to 0
*/

int						break_des_ecb(t_parse *p)
{
	uint64_t		i;
	int			fd_log;
	uint64_t		log_tic;

	if ((fd_log = open("crypta.log", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1
		&& ft_dprintf(2, "%sopen error on crypta log%s\n", KRED, KNRM))
		return (-1);
	ft_dprintf(2, g_ssl_str[CRYPTA_DESECB_RUNNING], KYEL, KNRM);
	ft_dprintf(fd_log, g_ssl_str[CRYPTA_VAR_SUFFIX]);
	ft_dprintf(fd_log, "plaintext_le = %#018lx\n", p->c.p);
	ft_dprintf(fd_log, "ciphertext_le = %#018lx\n", p->c.c);
	log_tic = ft_power(2, 21);
	ft_dprintf(fd_log, "log_tic = %#018lx\n\n", log_tic);
	i = -1;
	while (++i < 0x0100000000000000 && !is_key(p, pbd(i), fd_log, log_tic))
		continue ;
	if (++i == 0x0100000000000000)
		ft_dprintf(fd_log, g_ssl_str[CRYPTA_ERR_DEC]);
	close(fd_log);
	return (-1);
}
