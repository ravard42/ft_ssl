#include "libft.h"

void	*ft_memrev(void *p, size_t n)
{
	unsigned char	*str;
	unsigned char	tmp;
	size_t			i;

	str = (unsigned char *)p;
	i = -1;
	while (++i < n / 2)
	{
		tmp = str[i];
		str[i] = str[n - i - 1];
		str[n - i - 1] = tmp;
	}
	return (p);
}
