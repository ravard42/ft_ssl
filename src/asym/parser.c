#include "ft_ssl.h"

/*
** rsa key order : version, n, e, d, p, q, dp, dq, qinv
*/

/*
** NEED to be clear with sym parser (especially with segv.log on sym process)
** then we 'll use this parser architecture for asym parser (maybe on by cmd: genrsa, rsa, rsautl)
*/


//int				sym_parser(int argc, char **argv, t_parse *p)
//{
//	(void)argc;
//	while (argv[++p->i[0]])
//	{
//		if (argv[p->i[0]][0] != '-'
//			&& ft_dprintf(2, "%serror: '%s' bad input argument%s\n",
//				KRED, argv[p->i[0]], KNRM))
//			return (usage());
//		if (!opt_parser(argv[p->i[0]], p))
//			return (0);
//		if ((!p->in_file && p->o[7])
//				|| (!p->out_file && p->o[8])
//				|| (!p->s.arg[0].set && p->o[10])
//				|| (!p->s.arg[1].set && p->o[11])
//				|| (!p->s.arg[2].set && p->o[12])
//				|| (!p->s.arg[3].set && p->o[13]))
//			if (!load_args(p, argv[++p->i[0]]))
//				return (0);
//	}
//	return (arg_feed_verif(p));
//}
