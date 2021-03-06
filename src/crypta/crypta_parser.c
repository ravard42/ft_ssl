/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crypta_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 18:16:53 by user42            #+#    #+#             */
/*   Updated: 2020/06/10 18:17:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char		*g_crypta_opt[] = {"-p", "-c", ""};
static const char		*g_crypta_usg[] = {
	"-p plaintext_file",
	"-c ciphertext_file",
	""
};

/*
** cf include/commands.h
** type == 3 <=> C-C-C_Combo_Breaker Bonus (Cryptanalysis)
** we use command nb_k value in this mode to determine the block cipher size,
**	i-e the length of plaintext and related ciphertext data needed at least
**	for attempting cryptanalysis on it (e.g: 8 for des)
*/

static bool		load_text(uint64_t *text, int argc, char **argv, t_parse *p)
{
	int	fd;

	if (++p->i[0] >= argc && ft_dprintf(2, "%smiss arg%s\n", KRED, KNRM))
		return (false);
	if ((fd = open(argv[p->i[0]], O_RDONLY)) == -1
		&& ft_dprintf(2, "%sopen error%s\n", KRED, KNRM))
		return (false);
	if (read(fd, text, p->cmd.nb_k) < p->cmd.nb_k
		&& ft_dprintf(2, g_ssl_str[CRYPTA_ERR_LEN],
		KRED, p->cmd.nb_k * 8, KNRM))
		return (false);
	return (true);
}

int				crypta_parser(t_parse *p, int argc, char **argv)
{
	bool	set[2];

	p->c.o[0] = 0;
	p->c.o[1] = 0;
	set[0] = false;
	set[1] = false;
	while (++p->i[0] < argc)
	{
		if (!opt_parser(p, g_crypta_opt, argv[p->i[0]]))
			return (opt_usage("crypta opts", g_crypta_usg));
		if (!set[0] && p->c.o[0] == 1
			&& !(set[0] = load_text(&p->c.p, argc, argv, p)))
			return (-2);
		if (!set[1] && p->c.o[1] == 1
			&& !(set[1] = load_text(&p->c.c, argc, argv, p)))
			return (-2);
	}
	if ((!set[0] || !set[1])
		&& ft_dprintf(2, g_ssl_str[CRYPTA_ERR_DATA], KRED, KNRM))
		return (-2);
	return (1);
}
