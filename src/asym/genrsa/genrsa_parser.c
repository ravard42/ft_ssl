/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:29:55 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 21:49:34 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		numbits(char *nb)
{
	int16_t		ret;

	if (!ft_is_decimal(nb)
		&& ft_dprintf(2, g_ssl_str[GRSA_ERR_NB_0], KRED, nb, KNRM))
		return (-1);
	ret = (int16_t)ft_atoi(nb);
	if (ret < 64
		&& ft_dprintf(2, g_ssl_str[GRSA_ERR_NB_1], KRED, KNRM))
		return (-1);
	else if (ret > 2048
		&& ft_dprintf(2, g_ssl_str[GRSA_ERR_NB_2], KRED, KNRM))
		return (-1);
	return (ret);
}

static bool		seed_with_file(t_parse *p)
{
	close(p->rng.fd);
	if ((p->rng.fd = open(p->in_file, O_RDONLY)) == -1
		&& ft_dprintf(2, "%sopen rng seed file error%s\n", KRED, KNRM))
		return (false);
	return (true);
}

static bool		init_rsak(t_asym *a)
{
	if (!(a->rsak = (t_varint *)ft_memalloc(sizeof(t_varint) * 9))
		&& ft_dprintf(2, "%srsak malloc error%s\n", KRED, KNRM))
		return (false);
	return (true);
}

static const char		*g_grsa_opt[] = {"-rand", "-out", ""};
static const char		*g_grsa_usg[] = {
	"-rand file, use file to seed the random number generator " \
	"(default /dev/urandom)",
	"-out file (default stdout)",
	"numbits, size of the modulus between 64 (default) and 2048 " \
	"(must be the last option specified)",
	""
};

int				genrsa_parser(t_parse *p, int argc, char **argv)
{
	if (!init_rsak(&p->a))
		return (-2);
	while (++p->i[0] < argc)
	{
		if (p->i[0] == argc - 1)
		{
			if ((p->a.mod_nb = numbits(argv[p->i[0]])) == -1)
				return (opt_usage("genrsa opts", g_grsa_usg));
		}
		else
		{
			if (!opt_parser(p, g_grsa_opt, argv[p->i[0]]))
				return (opt_usage("genrsa opts", g_grsa_usg));
			if (!p->in_file && p->a.o[0])
				if (!(p->in_file = ft_strdup(argv[++p->i[0]])))
					return (-2);
			if (!p->out_file && p->a.o[1])
				if (!(p->out_file = ft_strdup(argv[++p->i[0]])))
					return (-2);
		}
	}
	if (p->in_file && !seed_with_file(p))
		return (-2);
	return (1);
}
