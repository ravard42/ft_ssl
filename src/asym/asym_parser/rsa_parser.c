#include "ft_ssl.h"

/*
**	io_parser
**
** -in|-out file
*/

static char		*io_parser(t_parse *p, int argc, char **argv)
{
	char		*file_name;

	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-in|-out need arg%s\n", KRED, KNRM))
		return (NULL);
	if (!(file_name = ft_strdup(argv[p->i[0]]))
		&& ft_dprintf(2, "%sio_parser error%s\n", KRED, KNRM))
		return (NULL);
	return (file_name);
}

/*
**	form_parser
**
** -inform|-outform PEM (default)
** -inform|-outform DER
*/

static bool		form_parser(t_parse *p, int argc, char **argv)
{
	uint8_t	tmp;

	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-inform need a value (PEM|DER)%s\n", KRED, KNRM))
		return (false);
	if (!ft_strcmp("PEM", argv[p->i[0]]))
		tmp = 0;
	else if (!ft_strcmp("DER", argv[p->i[0]]))
		tmp = 2;
	else
	{
		ft_dprintf(2, "%s-inform invalid format (available : PEM|DER)%s\n", KRED, KNRM);
		return (false);
	}
	p->a.o[2] = (p->a.o[2] == 1) ? tmp : p->a.o[2];
	p->a.o[3] = (p->a.o[3] == 1) ? tmp : p->a.o[3];
	return (true);
}

/*
**	pw_parser
**
** -passin|-passout pass:password
** -passin|-passout file:pathname
**
**	if file:pathname
**		the password string is read on the first line of the file
*/

static char		*load_pw(int8_t mode, char *pw_in)
{
	int		fd;
	char		*pw;

	pw = NULL;
	if (mode == 0)
		pw = ft_strdup(pw_in);
	else if (mode == 1)
	{
		if ((fd = open(pw_in, O_RDONLY)) == -1
			&& ft_dprintf(2, "%sCan't open password file%s\n", KRED, KNRM))
			return (NULL);
		get_next_line(fd, &pw);
		close(fd);
	}
	if (pw == NULL)
		ft_dprintf(2, "%spw_parser error%s\n", KRED, KNRM);
	else if (ft_strlen(pw) < 4
		&& ft_dprintf(2, "%spassword need at least 4 char%s\n", KRED, KNRM))
	{
		free(pw);
		pw = NULL;
	}
	return (pw); 
}

static char		*pw_parser(t_parse *p, int argc, char **argv)
{
	int8_t	mode;

	if (++p->i[0] >= argc
		&& ft_dprintf(2, "%s-passin|-passout need arg%s\n", KRED, KNRM))
		return (NULL);
	if (!ft_strncmp("pass:", argv[p->i[0]], 5))
		mode = 0;
	else if (!ft_strncmp("file:", argv[p->i[0]], 5))
		mode = 1;
	else
	{
		ft_dprintf(2, "%s-passin|-passout bad arg keyword%s\n", KRED, KNRM);
		return (NULL);
	}
	return (load_pw(mode, argv[p->i[0]] + 5));
}

static const char		*g_rsa_opt[] = {"-in", "-out", "-inform", "-outform", "-passin", "-passout", "-des", "-pubin", "-pubout", "-text", "-modulus", "-noout", "-check", ""};
static const char		*g_rsa_usg[] = {IN, OUT, IF, OF, PI, PO, ENC, PBI, PBO, T, M, N, C, ""};

int				rsa_parser(t_parse *p, int argc, char **argv)
{
	while (++p->i[0] < argc)
	{
		if (!opt_parser(p, g_rsa_opt, argv[p->i[0]]))
			return (opt_usage("rsa opts", g_rsa_usg));
		if (!p->in_file && p->a.o[0]
			&& !(p->in_file = io_parser(p, argc, argv)))
			return (-2);
		if (!p->out_file && p->a.o[1]
			&& !(p->out_file = io_parser(p, argc, argv)))
			return (-2);
		if ((p->a.o[2] == 1 || p->a.o[3] == 1)
			&& !form_parser(p, argc, argv))
			return (-2);
		if (!p->s.arg[0].p && p->a.o[4]
			&& !(p->s.arg[0].p = pw_parser(p, argc, argv)))
			return (-2);
		if (!p->s.arg[1].p && p->a.o[5]
			&& !(p->s.arg[1].p = pw_parser(p, argc, argv)))
			return (-2);
	}
	if (ft_read(&p->r, p->in_file) < 0)
		return (-2);
	if (p->a.o[6] && !p->s.arg[1].p && !(p->s.arg[1].p = set_pass(true)))
		return (-2);
	return (1);
}
