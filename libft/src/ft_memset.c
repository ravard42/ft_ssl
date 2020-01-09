#include "libft.h"

void			ft_memset(char *b, char c, size_t len)
{
	size_t			i;

	i = -1;
	while (++i < len)
		b[i] = c;
}
