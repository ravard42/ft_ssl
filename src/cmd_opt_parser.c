/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_opt_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:03:40 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:28:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		load_cmd(t_cmd *cmd, const t_cmd *src)
{
	uint16_t			endian_sys;

	cmd->type = src->type;
	ft_memcpy(cmd->name, src->name, ft_strlen(src->name) + 1);
	endian_sys = 1;
	endian_sys = *((uint8_t *)&endian_sys) ? 0 : 1;
	if (src->endian != -1)
	{
		cmd->endian = src->endian;
		cmd->endian |= endian_sys << 1;
		cmd->endian |= (cmd->endian == 1 || cmd->endian == 2) ? 4 : 0;
	}
	else
		cmd->endian = endian_sys;
	cmd->hash_hex_len = src->hash_hex_len;
	cmd->needed[0] = src->needed[0];
	cmd->needed[1] = src->needed[1];
	cmd->needed[2] = src->needed[2];
	cmd->nb_k = src->nb_k;
	cmd->parser = src->parser;
	cmd->run = src->run;
	cmd->run_e = src->run_e;
	cmd->run_d = src->run_d;
	return (1);
}

int				cmd_parser(char *arg, t_parse *p)
{
	int				i;
	int				j;

	i = -1;
	while (ft_strcmp(g_cmds[++i].name, "")
			&& (j = ft_strcmp(g_cmds[i].name, arg)))
		;
	if (j == 0)
		return (load_cmd(&(p->cmd), g_cmds + i));
	ft_dprintf(2, "%s\"%s\" is not a valid command, program leaving [...]%s\n",
			KRED, arg, KNRM);
	return (0);
}

int				opt_parser(char *arg, t_parse *p)
{
//	static char		*opt[] = {"-p", "-q", "-r", "-s", "", 
//						"-e", "-d", "-i", "-o", "-a",
//						"-k", "-v", "-s", "-p", "",
//						}};
	static char		*h_opt[] = {"-p", "-q", "-r", "-s", ""};
	static char		*s_opt[] = {"-e", "-d", "-i", "-o", "-a",
							"-k", "-v", "-s", "-p", ""};
	int				i;
	int				j;

	j = 0;
	i = -1;
	if (p->cmd.type == 1)
		while (ft_strcmp(h_opt[++i], "")
			&& (j = ft_strcmp(arg, h_opt[i])))
			;
	else if (p->cmd.type == 2)
		while (ft_strcmp(s_opt[++i], "")
			&& (j = ft_strcmp(arg, s_opt[i])))
			;
	if (j == 0 && p->cmd.type == 1)
		return (p->o[i + 1] = 1);
	else if (j == 0 && p->cmd.type == 2)
		return (p->o[i + 1 + 4] = 1);
	ft_dprintf(2, "%s\"%s\" is not a valid option%s\n", KRED, arg, KNRM);
	return (0);
}
