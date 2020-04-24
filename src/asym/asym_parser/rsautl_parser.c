#include "ft_ssl.h"

/*
**	io_parser
**
** -in|-out|-inkey file
**	a]	-in		:	we use p->a.data to store -in arg
**	b]	-out		:	we use p->out_file to load -out arg file name.
**	c] -inkey	:	here we use p->in_file and p->r to load -inkey key.pem
**						endeed it will be more convenient to use read_rsak in the same way that rsa command
*/

static bool		in_parser(t_parse *p, int argc, char **argv)
{
	p->a.o[0] = 0;
	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-in needs arg%s\n", KRED, KNRM))
		return (false);
	if (ft_read(&p->a.data, argv[p->i[0]]) < 0
		&& ft_dprintf(2, "%s-in parser error%s\n", KRED, KNRM))
		return (false);
	return (true);
}

static bool		out_parser(t_parse *p, int argc, char **argv)
{
	p->a.o[1] = 0;
	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-out needs arg%s\n", KRED, KNRM))
		return (false);
	if (!(p->out_file = ft_strdup(argv[p->i[0]]))
		&& ft_dprintf(2, "%s-out parser error%s\n", KRED, KNRM))
		return (false);
	return (true);
}

static bool		inkey_parser(t_parse *p, int argc, char **argv)
{
	p->a.o[2] = 0;
	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-inkey needs arg%s\n", KRED, KNRM))
		return (false);
	if ((!(p->in_file = ft_strdup(argv[p->i[0]]))
		|| ft_read(&p->r, p->in_file) < 0)
		&& ft_dprintf(2, "%s-inkey parser error%s\n", KRED, KNRM))
		return (false);
	return (true);

}

static const char		*g_rsau_opt[] = {"-in", "-out", "-inkey", "-pubin", "-encrypt", "-decrypt", "-hexdump", "-raw"};
static const char		*g_rsau_usg[] = {IN, OUT, IK, PBI2, RSA_E, RSA_D, HEXD, RAW, ""};

int				rsautl_parser(t_parse *p, int argc, char **argv)
{
	while (++p->i[0] < argc)
	{
		if (!opt_parser(p, g_rsau_opt, argv[p->i[0]]))
			return (opt_usage("rsautl opts", g_rsau_usg));
		if (p->a.data.len == -1 && p->a.o[0] && !in_parser(p, argc, argv))
			return (-2);
		if (!p->out_file && p->a.o[1] && !out_parser(p, argc, argv))
			return (-2);
		if (!p->in_file && p->a.o[2] && !inkey_parser(p, argc, argv))
			return (-2);
	}
	if (!p->in_file && ft_dprintf(2, ERR_OPT_0, KRED, KNRM))
		return (-2);
	if (!p->a.o[4] && !p->a.o[5] && ft_dprintf(2, ERR_OPT_1, KRED, KNRM))
		return (-2);
	if (p->a.data.len == -1 && ft_read(&p->a.data, NULL) < 0)
		return (-2);
	if (p->a.data.len > V_MAX_LEN
		&& ft_dprintf(2, ERR_DATA_LEN, KRED, p->a.data.len, KNRM))
		return (-2);
	return (1);
}
