/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:38:26 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 02:36:44 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char		*g_sym_usg[] = {E, D, I, O,
	DES, A, K, V, SALT, PW, ""};

static const char		*g_sym_opt[] = {"-e", "-d", "-i", "-o", "-a",
	"-k", "-v", "-s", "-p", ""};

void			format_key(t_sym *s, uint8_t nb_k)
{
	uint8_t	i;

	i = -1;
	while (++i < nb_k)
	{
		*(s->arg[0].x + i) = (s->endian) ?
			*(s->arg[0].x + i)
			: bswap64(*(s->arg[0].x + i));
		load_sub_k(s, i);
	}
}

static int		set_arg(t_parse *p, int id, char *arg)
{
	if (id == 0)
	{
		if (!(hstr_to_64_t(p->s.arg[0].x, p->cmd.nb_k, arg, true)))
			return (0);
		format_key(&p->s, p->cmd.nb_k);
	}
	else if (id == 1 || id == 2)
	{
		if (!(hstr_to_64_t(p->s.arg[id].x, 1, arg, true)))
			return (0);
	}
	else if (id == 3)
		if (!(p->s.arg[3].p = ft_strdup(arg)))
			return (0);
	p->s.arg[id].set = true;
	return (1);
}

static int		load_args(t_parse *p, char *arg)
{
	int		i;

	if (!arg && ft_dprintf(2, "%sarg is missing%s\n", KRED, KNRM))
		return (0);
	if (!p->in_file && p->s.o[2])
		if (fd_parser(p, arg) < 0)
			return (0);
	if (!p->out_file && p->s.o[3])
		if (!(p->out_file = ft_strdup(arg)))
			return (0);
	i = -1;
	while (++i < 4)
		if (!p->s.arg[i].set && p->s.o[5 + i])
			if (!set_arg(p, i, arg))
				return (0);
	return (1);
}

static int		arg_feed_verif(t_parse *p)
{
	if ((p->s.arg[0].set || p->s.arg[1].set) && p->s.arg[2].set
		&& ft_dprintf(2, "%scan't use -k/-v and -s at the same time%s\n",
			KRED, KNRM))
		return (-3);
	if (!p->s.o[1])
	{
		if (p->cmd.needed[0] && !p->s.arg[0].set && !pbkdf(p, true, NULL))
			return (-3);
		if (p->cmd.needed[1] && !p->s.arg[1].set
			&& ft_dprintf(2, "%sInitialization vector undefined%s\n",
				KRED, KNRM))
			return (-3);
	}
	if (!p->in_file && !fd_parser(p, NULL))
		return (-3);
	return (1);
}

int				sym_parser(t_parse *p, int argc, char **argv)
{
	while (++p->i[0] < argc)
	{
		if (!opt_parser(p, g_sym_opt, argv[p->i[0]]))
			return (opt_usage("Cipher opts", g_sym_usg));
		if ((!p->in_file && p->s.o[2])
				|| (!p->out_file && p->s.o[3])
				|| (!p->s.arg[0].set && p->s.o[5])
				|| (!p->s.arg[1].set && p->s.o[6])
				|| (!p->s.arg[2].set && p->s.o[7])
				|| (!p->s.arg[3].set && p->s.o[8]))
			if (!load_args(p, argv[++p->i[0]]))
				return (-3);
	}
	return (arg_feed_verif(p));
}
