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
	free_if((void **)&a->rsak);
	free_if((void **)&a->data.msg);
	a->data.len = 0;
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
		free_if((void **)&p->in_file);
		free_if((void **)&p->r.msg);
		p->r.len = 0;
		free_if((void **)&p->out_file);
		if (p->w.fd > 1)
			close(p->w.fd);
		p->w.fd = -1;
		free_if((void **)&p->w.msg);
		p->w.len = 0;
	}
//	free_h(&p->h, free_opt & 2);
	free_s(&p->s, free_opt & 4);
	free_a(&p->a, free_opt & 8);
	free_rng(&p->rng, free_opt & 16);
}
