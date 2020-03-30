#include "ft_ssl.h"

//void			free_h(t_hash *h, bool freee)
//{
//	if (!freee)
//		return ;
//}


void			free_s(t_sym *s, bool freee)
{
	int	i = -1;	

	if (!freee)
		return ;
	while (++i < 4)
	{
		if (s->arg[i].p)
			free(s->arg[i].p);
		s->arg[i].p = NULL;
		s->arg[i].set = false;
	}
}

void			free_a(t_asym *a, bool freee)
{
	if (!freee)
		return ;
	if (a->rsak)
		free(a->rsak);
	a->rsak = NULL;
}

void			free_rng(t_rng *rng, bool freee)
{
	if (!freee)
		return ;
	if (rng->fd > 1)
		close(rng->fd);
	rng->fd = -1;
}

/*
**	free_opt			
**		1		->		p (i, r, in_file, w, out_file)
**		2		->		h
**		4		->		s
**		8		->		a
**		16		->		rng
**	NB: combinable
**		 exempli gratia/e.g: 
**		 free_opt == 31 (01111)
**		 will free  p(i, r, in_file, w, out_file)
**					 + h
**					 + s
**					 + a
**					 + rng
*/

void			free_p(t_parse *p, uint8_t free_opt)
{
	if (free_opt & 1)
	{
//		if (p->in_file)
//			free(p->in_file);
//		p->in_file = NULL;
//		if (p->r.msg)
//			free(p->r.msg);
//		p->r.msg = NULL;
		free_if((void **)&p->in_file);
		free_if((void **)&p->r.msg);
		p->r.len = 0;
		free_if((void **)&p->out_file);
		if (p->w.fd > 1)
			close(p->w.fd);
		p->w.fd = -1;
		free_if((void **)&p->w.msg);
//		if (p->w.msg)
//			free(p->w.msg);
//		p->w.msg = NULL;
		p->w.len = 0;
//		if (p->out_file)
//			free(p->out_file);
//		p->out_file = NULL;
	}
//	free_h(&p->h, free_opt & 2);
	free_s(&p->s, free_opt & 4);
	free_a(&p->a, free_opt & 8);
	free_rng(&p->rng, free_opt & 16);
}
