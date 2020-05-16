#include "ft_ssl.h"

static const char		*g_crypta_opt[] = {"-k", "-a", "-p", ""};
static const char		*g_crypta_usg[] = {
	"-k keysize",
	"-a algo",
	"-p plaintext",
	""
};

int				crypta_parser(t_parse *p, int argc, char **argv)
{
	ft_dprintf(1, "%scrypta_parser entrance%s\n", KMAG, KNRM);
	while (++p->i[0] < argc)
	{
			if (!opt_parser(p, g_crypta_opt, argv[p->i[0]]))
				return (opt_usage("crypta opts", g_crypta_usg));
//			if (!p->in_file && p->a.o[0])
//				if (!(p->in_file = ft_strdup(argv[++p->i[0]])))
//					return (-2);
//			if (!p->out_file && p->a.o[1])
//				if (!(p->out_file = ft_strdup(argv[++p->i[0]])))
//					return (-2);
	}
	return (1);
}
