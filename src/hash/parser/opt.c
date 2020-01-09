#include "ft_ssl.h"

int				hash_opt(t_parse *p, char *arg)
{
	static char		*opt[] = {"-p", "-q", "-r", "-s", ""};
	int				i;
	int				j;

	j = 0;
	i = -1;
	while (ft_strcmp(opt[++i], "")
		&& (j = ft_strcmp(opt[i], arg)))
		;
	if (j == 0)
		return (p->h.o[i + 1] = 1);
	ft_dprintf(2, "%s\"%s\" is not a valid option%s\n", KRED, arg, KNRM);
	return (0);
}
