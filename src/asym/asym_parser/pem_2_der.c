#include "ft_ssl.h"

/*
** grep_pem
**
** scan t_read *r to find a pem valid sequence.
**	
*/


int		grep_pem(t_parse *p)
{
	char		*str[2];
	int64_t	offset;
	size_t	len;

	str[0] = (p->a.o[7]) ? PEM_PUB_BEG : PEM_PRI_BEG;
	str[1] = (p->a.o[7]) ? PEM_PUB_END : PEM_PRI_END;
	offset = 0;
	len = ft_strlen(str[0]);
	while (p->r.len - offset >= len && ft_strncmp(p->r.msg + offset, str[0], ft_strlen(str[0])))
	{
		if ((tmp = ft_nxt_line(offset, &p->r)) <= 0)
			return (0);
		offset += tmp;
	}
	if (p->r.len - offset < len)
		return (0);

	ft_printf("FOUNF IT!\n");
	return (1);

}
