/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:01:24 by ravard            #+#    #+#             */
/*   Updated: 2020/01/29 07:09:30 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** beginning to end0 	: Standard commands
** between end0 and end1 : Message Digest commands
** between end1 and end2 : Cipher commands
*/

static const char	*g_cmd_name[] = {
	"genrsa", "\x1B[36;1mrsa (to be computed)",
	"rsautl (to be computed)", "end0",
	"md5", "sha256", "end1",
	"base64", "des-ecb", "des-cbc", "des", "des-ofb", "des-cfb",
	"des-ede3", "des-ede3-cbc", "des3", "des-ede3-ofb", "des-ede3-cfb", "end2"
};

int				cmd_usage(void)
{
	int				i;

	ft_dprintf(2, U, KGRN, KWHT, KBLU, KYEL, KWHT);
	i = -1;
	ft_dprintf(2, "\n%sStandard commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end0", g_cmd_name[++i]))
		ft_dprintf(2, " %s\n", g_cmd_name[i]);
	ft_dprintf(2, "\n%sMessage Digest commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end1", g_cmd_name[++i]))
		ft_dprintf(2, " %s\n", g_cmd_name[i]);
	ft_dprintf(2, "\n%sCipher commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end2", g_cmd_name[++i]))
		ft_dprintf(2, " %s\n", g_cmd_name[i]);
	return (1);
}

int				opt_usage(char *title, const char **usg)
{
	int	i;

	i = -1;
	ft_dprintf(2, "%s%s%s:\n", KYEL, title, KNRM);
	while (ft_strcmp(usg[++i], ""))
		ft_dprintf(2, " %s\n", usg[i]);
	return (-3);
}
