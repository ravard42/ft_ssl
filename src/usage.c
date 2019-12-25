/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:01:24 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 15:03:07 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**beginning to end0 : Standard commands
**between end0 and end1 : Message Digest commands
**between end1 and end2 : Cipher commands
*/

static void			cmds_usage(void)
{
	static char		*cmds[] = {"end0", "md5", "sha256", "end1",
			"base64", "des-ecb", "des-cbc", "des", "des-ofb", "des-cfb",
			"des-ede3", "des-ede3-cbc", "des3", "des-ede3-ofb", "des-ede3-cfb", "end2"};
	int				i;

	i = -1;
	ft_dprintf(2, "\n%sStandard commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end0", cmds[++i]))
		ft_dprintf(2, " %s\n", cmds[i]);
	ft_dprintf(2, "\n%sMessage Digest commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end1", cmds[++i]))
		ft_dprintf(2, " %s\n", cmds[i]);
	ft_dprintf(2, "\n%sCipher commands%s:\n", KBLU, KNRM);
	while (ft_strcmp("end2", cmds[++i]))
		ft_dprintf(2, " %s\n", cmds[i]);
}

/*
**beginning to end0 : Standard command options
**between end0 and end1 : Message Digest command options
**between end1 and end2 : Cipher command options
*/

static void			opts_usage(void)
{
	static char		*opts[] = {"end0",
									P, Q, R, S, "end1",
									E, D, I, O,
									DES_ONLY, A, K, V, SALT, PW, "end2"};
	int				i;

	i = -1;
	ft_dprintf(2, "\n%sStandard opts%s:\n", KYEL, KNRM);
	while (ft_strcmp("end0", opts[++i]))
		ft_dprintf(2, " %s\n", opts[i]);
	ft_dprintf(2, "\n%sMessage Digest opts%s:\n", KYEL, KNRM);
	while (ft_strcmp("end1", opts[++i]))
		ft_dprintf(2, " %s\n", opts[i]);
	ft_dprintf(2, "\n%sCipher opts%s:\n", KYEL, KNRM);
	while (ft_strcmp("end2", opts[++i]))
		ft_dprintf(2, " %s\n", opts[i]);
}

int					usage(void)
{
	ft_dprintf(2, U, KGRN, KWHT, KBLU, KYEL, KWHT);
	cmds_usage();
	opts_usage();
	return (0);
}
