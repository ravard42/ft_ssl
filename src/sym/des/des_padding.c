/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:11:10 by ravard            #+#    #+#             */
/*   Updated: 2020/01/31 00:58:40 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char			*des_padding(t_parse *p)
{
	t_read	tmp;
	uint8_t	r;

	tmp.len = 8 * (p->r.len / 8 + 1);
	r = p->r.len % 8;
	if (!(tmp.msg = (char *)ft_memalloc(sizeof(char) * tmp.len)))
		return (NULL);
	ft_memcpy(tmp.msg, p->r.msg, p->r.len);
	ft_memset(tmp.msg + p->r.len, 8 - r, 8 - r);
	free(p->r.msg);
	p->r.msg = tmp.msg;
	p->r.len = tmp.len;
	return (p->r.msg);
}

int64_t			des_unpadding(t_write *w)
{
	uint8_t	unpad;
	uint8_t	i;

	unpad = *((uint8_t *)(w->msg + w->len) - 1);
	if (unpad > 0 && unpad <= 8)
	{
		i = 1;
		while (++i <= unpad)
			if (*((uint8_t *)(w->msg + w->len) - i) != unpad)
				break ;
		if (i == unpad + 1)
			return (unpad);
	}
	return (0);
}
