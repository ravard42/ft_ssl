#include "ft_ssl.h"

int		sha256_pbkdf(t_parse *tmp, t_parse *p)
{
	init_p(tmp, "sha256");
	tmp->h.pbkdf = true;

	tmp->r.len = ft_strlen(p->s.arg[3].p) + 8;
	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
	ft_memcpy(tmp->r.msg, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
	ft_memcpy(tmp->r.msg + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
	if (!tmp->cmd.run(tmp))
		return (0);
	return (1);
}


static int			nxt_md5_pbkdf_round(t_parse *tmp, uint32_t *h_tmp, t_parse *p)
{
	init_p(tmp, "md5");
	tmp->h.pbkdf = true;

	tmp->r.len = 16 + ft_strlen(p->s.arg[3].p) + 8;
	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
	ft_memcpy(tmp->r.msg, h_tmp, 16);
	ft_memcpy(tmp->r.msg + 16, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
	ft_memcpy(tmp->r.msg + 16 + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
	if (!tmp->cmd.run(tmp))
		return (0);
	return (1);
}

int					md5_pbkdf(t_parse *tmp, t_parse *p)
{
	uint32_t	h_tmp[4];

	init_p(tmp, "md5");
	tmp->h.pbkdf = true;

	tmp->r.len = ft_strlen(p->s.arg[3].p) + 8;
	tmp->r.msg = ft_memalloc(sizeof(char) * (tmp->r.len));
	ft_memcpy(tmp->r.msg, p->s.arg[3].p, ft_strlen(p->s.arg[3].p));
	ft_memcpy(tmp->r.msg + ft_strlen(p->s.arg[3].p), p->s.arg[2].x, 8);
	if (!tmp->cmd.run(tmp))
		return (0);
	if (p->cmd.nb_k == 1)
		return (1);
	ft_memcpy(h_tmp, tmp->h.h, 16);
	if (!nxt_md5_pbkdf_round(tmp, h_tmp, p))
		return (0);
	ft_memcpy(tmp->h.h + 4, tmp->h.h, 16);
	ft_memcpy(tmp->h.h, h_tmp, 16);
	return (1);
}
