/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:06:05 by ravard            #+#    #+#             */
/*   Updated: 2018/03/10 16:32:11 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*find_type(int *offset, char const *s, t_spe *sp)
{
	int					i;
	char				*buff;

	buff = buff_malloc(offset, s, sp);
	i = -1;
	while (s[++i] != sp->type)
		buff[i] = s[i];
	buff[i] = '\0';
	sp->type = (sp->type == 'i') ? 'd' : sp->type;
	return (buff);
}

static void				catch_flags(char *s, t_spe *sp)
{
	int		field;
	int		i;

	field = 0;
	i = -1;
	while (s[++i])
	{
		field = ((s[i] > '0' && s[i] <= '9') || s[i] == '.') ? 1 : field;
		sp->fl.hash = (s[i] == '#') ? 1 : sp->fl.hash;
		sp->fl.min = (s[i] == '-') ? 1 : sp->fl.min;
		sp->fl.plu = (s[i] == '+') ? 1 : sp->fl.plu;
		sp->fl.sp = (s[i] == ' ') ? 1 : sp->fl.sp;
		sp->fl.ze = (s[i] == '0' && field == 0) ? 1 : sp->fl.ze;
	}
	sp->fl.sp = (sp->fl.plu) ? 0 : sp->fl.sp;
	sp->fl.ze = (sp->fl.min) ? 0 : sp->fl.ze;
}

static void				catch_w_and_pre(char *s, t_spe *sp)
{
	int		i;
	int		w_is_set;

	w_is_set = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '.')
		{
			sp->pre = catch_pos_numb(s + i + 1);
			break ;
		}
		if (s[i] > '0' && s[i] <= '9' && !w_is_set++)
			sp->w = catch_pos_numb(s + i);
	}
}

static void				catch_size(char *s, t_spe *sp)
{
	int		i;
	int		breakk;

	breakk = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 'h')
		{
			sp->size = (s[i + 1] == 'h') ? 'H' : 'h';
			i += (s[i + 1] == 'h') ? 1 : 0;
		}
		else if (s[i] == 'l' && (breakk = 1))
			sp->size = (s[i + 1] == 'l') ? 'L' : 'l';
		else if (s[i] == 'j' && (breakk = 1))
			sp->size = 'j';
		else if (s[i] == 'z' && (breakk = 1))
			sp->size = 'z';
		if (breakk)
			break ;
	}
}

int						extract_specifier(char const *s, t_spe *sp)
{
	int			offset;
	char		*buff;

	init_spe(sp);
	buff = find_type(&offset, s, sp);
	catch_flags(buff, sp);
	catch_w_and_pre(buff, sp);
	catch_size(buff, sp);
	free(buff);
	return (offset + 1);
}
