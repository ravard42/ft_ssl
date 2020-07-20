/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:00:57 by ravard            #+#    #+#             */
/*   Updated: 2020/05/13 22:03:43 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	io_parser
**
** -in|-out|-inkey file
**
**	a]	-in		:	we use p->a.data to store -in arg
**	b]	-out	:	we use p->out_file to load -out arg file name.
**	c] -inkey	:	here we use p->in_file and p->r to load -inkey key.pem
**					endeed it will be more convenient to use read_rsak
**					in the same way that rsa command
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

static const char		*g_rsau_opt[] = {"-in", "-out", "-inkey", "-pubin",
	"-encrypt", "-decrypt", "-hexdump", "-raw", ""};
static const char		*g_rsau_usg[] = {
	"-in file (default stdin)",
	"-out file (default stdout)",
	"-inkey val, input key",
	"-pubin, private key is read by default on -inkey, "\
	"with this option a public key is read instead",
	"-encrypt, encrypt with public key",
	"-decrypt, decrypt with private key",
	"-hexdump, hex dump the output data",
	"-raw, no padding applied (default PKCS#1 v1.5)",
	""
};

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
	if (!p->in_file && ft_dprintf(2, g_ssl_str[RSAU_ERR_OPT_0], KRED, KNRM))
		return (-2);
	if (!p->a.o[4] && !p->a.o[5]
			&& ft_dprintf(2, g_ssl_str[RSAU_ERR_OPT_1], KRED, KNRM))
		return (-2);
	if (p->a.data.len == -1 && ft_read(&p->a.data, NULL) < 0)
		return (-2);
	if (p->a.data.len > V_MAX_LEN
		&& ft_dprintf(2, g_ssl_str[RSAU_ERR_DATA_LEN_0],
			KRED, p->a.data.len, KNRM))
		return (-2);
	return (1);
}
