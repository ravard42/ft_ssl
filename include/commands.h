/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:07:33 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 00:54:48 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

typedef struct s_parse	t_parse;

typedef struct			s_cmd
{
	int8_t			type;
	char			name[15];
	char			endian;
	char			hash_hex_len;
	int				(*parser)(t_parse *, int, char **);
	bool			needed[3];
	uint8_t			nb_k;
	int				(*run)(t_parse *);
	int				(*run_e)(t_parse *);
	int				(*run_d)(t_parse *);
}						t_cmd;

/*
**	type == 0 <=> Standard command
**	type == 1 <=> Message Digest command
**	type == 2 <=> Cipher command
*/

/*
**needed <=> args which need to be feed at running
**needed[0] : key
**needed[1] : initial vector (64bit dans tous les cas)
**needed[2] : padding (only for sym cmd)
**nb_k == 1 <=> 64bit key needed : 56 used
**nb_k == 3	<=> 192bit key needed : 168 used
*/

int						hash_parser(t_parse *p, int argc, char **argv);
int						md5(t_parse *p);
int						sha256(t_parse *p);
int						sym_parser(t_parse *p, int argc, char **argv);
int						b64(t_parse *p);
int						des(t_parse *p);
int						ecb_e(t_parse *p);
int						ecb_d(t_parse *p);
int						cbc_e(t_parse *p);
int						cbc_d(t_parse *p);
int						ofb_e_d(t_parse *p);
int						cfb_e(t_parse *p);
int						cfb_d(t_parse *p);
int						ecb3_e(t_parse *p);
int						ecb3_d(t_parse *p);
int						cbc3_e(t_parse *p);
int						cbc3_d(t_parse *p);
int						ofb3_e_d(t_parse *p);
int						cfb3_e(t_parse *p);
int						cfb3_d(t_parse *p);
int						genrsa_parser(t_parse *p, int argc, char **argv);
int						genrsa(t_parse *p);
int						rsa_parser(t_parse *p, int argc, char **argv);
int						rsa(t_parse *p);
int						rsautl_parser(t_parse *p, int argc, char **argv);
int						rsautl(t_parse *p);

static const			t_cmd g_cmds[] = {
	{0, "genrsa", -1, -1, genrsa_parser,
		{false, false, false}, 3, genrsa, NULL, NULL},
	{0, "rsa", -1, -1, rsa_parser,
		{true, true, true}, 1, rsa, cbc_e, cbc_d},
	{0, "rsautl", -1, -1, rsautl_parser,
		{false, false, false}, 0, rsautl, NULL, NULL},
	{1, "md5", 0, 16, hash_parser,
		{false, false, false}, 0, md5, NULL, NULL},
	{1, "sha256", 1, 32, hash_parser,
		{false, false, false}, 0, sha256, NULL, NULL},
	{2, "base64", -1, -1, sym_parser,
		{false, false, false}, 0, b64, NULL, NULL},
	{2, "des-ecb", -1, -1, sym_parser,
		{true, false, true}, 1, des, ecb_e, ecb_d},
	{2, "des-cbc", -1, -1, sym_parser,
		{true, true, true}, 1, des, cbc_e, cbc_d},
	{2, "des", -1, -1, sym_parser,
		{true, true, true}, 1, des, cbc_e, cbc_d},
	{2, "des-ofb", -1, -1, sym_parser,
		{true, true, false}, 1, des, ofb_e_d, ofb_e_d},
	{2, "des-cfb", -1, -1, sym_parser,
		{true, true, false}, 1, des, cfb_e, cfb_d},
	{2, "des-ede3", -1, -1, sym_parser,
		{true, false, true}, 3, des, ecb3_e, ecb3_d},
	{2, "des-ede3-cbc", -1, -1, sym_parser,
		{true, true, true}, 3, des, cbc3_e, cbc3_d},
	{2, "des3", -1, -1, sym_parser,
		{true, true, true}, 3, des, cbc3_e, cbc3_d},
	{2, "des-ede3-ofb", -1, -1, sym_parser,
		{true, true, false}, 3, des, ofb3_e_d, ofb3_e_d},
	{2, "des-ede3-cfb", -1, -1, sym_parser,
		{true, true, false}, 3, des, cfb3_e, cfb3_d},
	{-1, "", 0, 0, NULL,
		{false, false, false}, 0, NULL, NULL, NULL}
};

#endif
