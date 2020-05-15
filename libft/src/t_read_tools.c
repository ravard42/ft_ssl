/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_read_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 03:14:34 by ravard            #+#    #+#             */
/*   Updated: 2020/05/12 03:14:35 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_nxt_line:
**
**	try to find a new starting line behind r->msg + offset
** (r->msg + offset excluded)
**
**	return the new offset if any new line
**	return -1 if none
**
**	NB : 	here r->msg + offset is not considering as a starting line
**			so ft_nxt_line can't return 0
**
**	return -2 for offset input error
*/

int64_t		ft_nxt_line(t_read *r, int64_t offset)
{
	if (offset >= r->len
		&& ft_dprintf(2, "%sft_nxt_line error%s\n", KRED, KNRM))
		return (-2);
	if (offset == r->len - 1)
		return (-1);
	while (r->msg[offset] != '\n')
	{
		offset++;
		if (offset == r->len - 1)
			return (-1);
	}
	return (++offset);
}

/*
** ft_grep_line:
**
**	try to find a line beginning by str in r->msg
**	starting from offset
** and considering r->msg + offset as the first candidate.
**
**	return the new offset if any matching line
**	return -1 if none
**
**	-2 for offset input error
*/

int64_t		ft_grep_line(const char *str, t_read *r, int64_t offset)
{
	int64_t	len;

	if (offset >= r->len
		&& ft_dprintf(2, "%sft_grep_line error%s\n", KRED, KNRM))
		return (-2);
	len = ft_strlen(str);
	while (r->len - offset >= len && ft_strncmp(r->msg + offset, str, len))
	{
		if ((offset = ft_nxt_line(r, offset)) <= 0)
			return (offset);
	}
	if (r->len - offset < len)
		return (-1);
	return (offset);
}
