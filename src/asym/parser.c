#include "ft_ssl.h"

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
