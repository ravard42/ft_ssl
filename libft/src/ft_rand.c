#include "libft.h"

/*
** uint64_t random number from /dev/urandom
** NB : [min, max[
*/

uint64_t	ft_rand(int urand_fd, uint64_t min, uint64_t max)
{
	uint64_t		ret;

	if (min > max
		&& ft_dprintf(2, "%sft_rand range error%s\n", KRED, KNRM))
		exit(0);
	if (read(urand_fd, (char *)&ret, 8) == -1
		&& ft_dprintf(2, "%s/dev/urandom read error%s\n", KRED, KNRM))
		exit(0);
	ret = (min == max) ? ret : min + ret % (max - min);
	return (ret);
}
