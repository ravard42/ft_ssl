#include "ft_ssl.h"

/*
** rsa key order : version, n, e, d, p, q, dp, dq, qinv
*/

static const char		*g_rsau_usg[] = {IN, OUT, IK, PBI, RSA_E, RSA_D, HEXD, ""};
static const char		*g_rsau_opt[] = {"-in", "-out", "-inkey", "-pubin", "-encrypt", "-decrypt", "hexdump", ""};

int				rsautl_parser(t_parse *p, int argc, char **argv)
{
	while (++p->i[0] < argc)
	{
		if (argv[p->i[0]][0] != '-'
			&& ft_dprintf(2, "%serror: '%s' bad input argument%s\n",
				KRED, argv[p->i[0]], KNRM))
			return (opt_usage("rsautl opts", g_rsau_usg));
		if (!opt_parser(p, g_rsau_opt, argv[p->i[0]]))
			return (opt_usage("rsautl opts", g_rsau_usg));
//		if ((!p->in_file && p->s.o[2])
//				|| (!p->out_file && p->s.o[3])
//				|| (!p->s.arg[0].set && p->s.o[5])
//				|| (!p->s.arg[1].set && p->s.o[6])
//				|| (!p->s.arg[2].set && p->s.o[7])
//				|| (!p->s.arg[3].set && p->s.o[8]))
//			if (!load_args(p, argv[++p->i[0]]))
//				return (0);
	}
	return (0);
}
