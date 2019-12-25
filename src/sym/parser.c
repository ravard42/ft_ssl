/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:38:26 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:40:36 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			format_key(t_parse *p)
{
	uint8_t	i;

	i = -1;
	while (++i < p->cmd.nb_k)
	{
		*(p->s.arg[0].x + i) = (p->cmd.endian) ?
			*(p->s.arg[0].x + i)
			: bswap64(*(p->s.arg[0].x + i));
		load_sub_k(&p->s, i);
	}
}

static int		set_arg(t_parse *p, int id, char *arg)
{
	if (id == 0)
	{
		if (!(hstr_to_64_t(p->s.arg[0].x, p->cmd.nb_k, arg)))
			return (0);
		format_key(p);
	}
	else if (id == 1 || id == 2)
	{
		if (!(hstr_to_64_t(p->s.arg[id].x, 1, arg)))
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
	if (!p->in_file && p->o[7])
		if (fd_parser(arg, p) < 0)
			return (0);
	if (!p->out_file && p->o[8])
		if (!(p->out_file = ft_strdup(arg)))
			return (0);
	i = -1;
	while (++i < 4)
		if (!p->s.arg[i].set && p->o[10 + i])
			if (!set_arg(p, i, arg))
				return (0);
	return (1);
}

static int		arg_feed_verif(t_parse *p)
{
	if ((p->s.arg[0].set || p->s.arg[1].set) && p->s.arg[2].set
		&& ft_dprintf(2, "%scan't use -k/-v and -s at the same time%s\n",
			KRED, KNRM))
		return (0);
	if (!p->o[6])
	{
		if (p->cmd.needed[0] && !p->s.arg[0].set && !pbkdf(p, true , NULL))
			return (0);
		if (p->cmd.needed[1] && !p->s.arg[1].set
			&& ft_dprintf(2, "%sInitialization vector undefined%s\n",
				KRED, KNRM))
			return (0);
	}
	if (!p->in_file)
		return (fd_parser(NULL, p));
	return (1);
}

int				sym_parser(int argc, char **argv, t_parse *p)
{
	(void)argc;
	while (argv[++p->i[0]])
	{
		if (argv[p->i[0]][0] != '-'
			&& ft_dprintf(2, "%serror: '%s' bad input argument%s\n",
				KRED, argv[p->i[0]], KNRM))
			return (usage());
		if (!opt_parser(argv[p->i[0]], p))
			return (0);
		if ((!p->in_file && p->o[7])
				|| (!p->out_file && p->o[8])
				|| (!p->s.arg[0].set && p->o[10])
				|| (!p->s.arg[1].set && p->o[11])
				|| (!p->s.arg[2].set && p->o[12])
				|| (!p->s.arg[3].set && p->o[13]))
			if (!load_args(p, argv[++p->i[0]]))
				return (0);
	}
	return (arg_feed_verif(p));
}
