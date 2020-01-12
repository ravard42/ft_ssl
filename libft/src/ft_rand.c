#include "libft.h"

/*
** ft_range : [min, max[
*/

uint64_t		ft_range(uint64_t src, uint64_t min, uint64_t max)
{
	if (min > max
		&& ft_dprintf(2, "%sft_range invalid (min, max) param%s\n", KYEL, KNRM))
		return (0);
	if (min == max)
		return (min);
	return (min + src % (max - min));
}

/*
** pseudo random number from /dev/urandom
** beware that dest have enough space memory for len bytes
*/

void		*ft_rand(void *dest, size_t len)
{
	int			fd;

	if (!dest
		&& ft_dprintf(2, "%sdest is null in ft_rand%s\n", KRED, KNRM))
		exit(0);
	if ((fd = open("/dev/urandom", O_RDONLY)) == -1
		&& ft_dprintf(2, "%s/dev/urandom open error%s\n", KRED, KNRM))
		exit(0);
	if (read(fd, (char *)dest, len) == -1
		&& ft_dprintf(2, "%s/dev/urandom read error%s\n", KRED, KNRM))
		exit(0);
	close(fd);
	return (dest);
}
