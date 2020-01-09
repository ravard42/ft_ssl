#include "ft_ssl.h"

int				sym_opt(t_parse *p, char *arg)
{
	static char		*opt[] = {"-e", "-d", "-i", "-o", "-a",
							"-k", "-v", "-s", "-p", ""};
	int				i;
	int				j;

	j = 0;
	i = -1;
	while (ft_strcmp(opt[++i], "")
		&& (j = ft_strcmp(opt[i], arg)))
		;
	if (j == 0)
		return (p->s.o[i] = 1);
	ft_dprintf(2, "%s\"%s\" is not a valid option%s\n", KRED, arg, KNRM);
	return (0);
}
