#include "libft.h"

bool		ft_is_decimal(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = -1;
	while (str[++i] && str[i] >= '0' && str[i] <= '9')
		;
	if (str[i])
		return (false);
	return (true);
}
