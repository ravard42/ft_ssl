/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 16:13:33 by ravard            #+#    #+#             */
/*   Updated: 2019/09/10 16:14:10 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			opt_a_e(t_parse *p)
{
	int	ret;

	if (p->r.msg)
		free(p->r.msg);
	p->r.msg = p->w.msg;
	p->r.len = p->w.len;
	p->w.msg = NULL;
	if ((ret = run_b64_e(p)) == -2)
		return (ret);
	return (1);
}

int			opt_a_d(t_parse *p)
{
	int	ret;

	if ((ret = run_b64_d(p)) == -2)
		return (ret);
	if (p->r.msg)
		free(p->r.msg);
	p->r.msg = p->w.msg;
	p->r.len = p->w.len;
	p->w.msg = NULL;
	return (1);
}
