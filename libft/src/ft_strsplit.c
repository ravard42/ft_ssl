/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:59:47 by ravard            #+#    #+#             */
/*   Updated: 2018/10/14 10:15:16 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*rm_begin_space(char *str, char c)
{
	int		begin;

	if (str[0] != c)
		return (str);
	begin = -1;
	while (str[++begin] == c)
		;
	ft_strcpy(str, str + begin);
	return (str);
}

static char		*rm_multi_space(char *str, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c && str[i + 1] == c)
		{
			tmp = str + i + 1;
			j = -1;
			while (tmp[++j] == c)
				;
			ft_strcpy(tmp, tmp + j);
		}
	}
	return (str);
}

static char		*symplify(const char *str, char c, int *word)
{
	char	*no_const;
	int		i;

	if ((no_const = ft_strdup(str)) == NULL)
		return (NULL);
	rm_begin_space(no_const, c);
	ft_revstr(rm_begin_space(ft_revstr(no_const), c));
	rm_multi_space(no_const, c);
	*word = (no_const[0] == '\0') ? 0 : 1;
	if (*word)
	{
		i = -1;
		while (no_const[++i])
			if (no_const[i] == c)
				(*word)++;
	}
	return (no_const);
}

static char		**load_tab(char *s, int *word, char c)
{
	int		i;
	char	*ptr[2];
	char	**tab;

	if ((tab = (char **)malloc(sizeof(char *) * (*word + 1))) == NULL)
		return (NULL);
	*ft_strchr(s, '\0') = c;
	ptr[0] = s;
	i = -1;
	while (++i < *word)
	{
		ptr[1] = ft_strchr(ptr[0], c);
		*ptr[1] = '\0';
		tab[i] = ft_strdup(ptr[0]);
		ptr[0] = ptr[1] + 1;
	}
	tab[i] = NULL;
	return (tab);
}

char			**ft_strsplit(const char *str, char c)
{
	int		word;
	char	*s;
	char	**ret;

	if (str == NULL)
		return (malloc_empty_str_tab());
	if ((s = symplify(str, c, &word)) == NULL)
		return (NULL);
	if (word == 0)
	{
		free(s);
		return (malloc_empty_str_tab());
	}
	else
		ret = load_tab(s, &word, c);
	free(s);
	return (ret);
}
