/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_free_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:58:54 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 10:42:04 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**malloc_empty_str_tab(void)
{
	char **ret;

	if ((ret = (char **)malloc(sizeof(char *))) == NULL)
		return (NULL);
	ret[0] = NULL;
	return (ret);
}

int			free_ok(void *ptr)
{
	free(ptr);
	return (1);
}

int			free_split(char **tab)
{
	int		i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (1);
}
