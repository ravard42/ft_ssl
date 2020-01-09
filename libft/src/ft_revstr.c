#include "libft.h"

char			*ft_revstr(char *str)
{
	int		len;
	char	tmp;
	int		i;

	len = ft_strlen(str);
	i = -1;
	while (++i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
	}
	return (str);
}
