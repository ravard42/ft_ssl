#include "libft.h"

size_t			ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t			ft_wstrlen(wchar_t *wc)
{
	int		i;

	i = -1;
	while (wc[++i])
		;
	return (i);
}
