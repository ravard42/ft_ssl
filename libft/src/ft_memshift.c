#include <libft.h>

/*
** Shift the len byte memory area starting at p by jump  
** user must ensure that shift memory stay in a valid memory allocated area
*/

void		*ft_memshift(void *p, ssize_t len, ssize_t jump)
{
	ssize_t		i;
	char			*str;

	str = (char *)p;
	if (jump < 0)
	{
		i = -1;
		while (++i < len)
			str[i + jump] = str[i];
	}
	else
	{
		i = len;
		while (--i >= 0)
			str[i + jump] = str[i];
	}
	return (str);
}
