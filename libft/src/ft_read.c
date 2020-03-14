/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 12:31:25 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:50:22 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		init_read_struct(t_read *p)
{
	p->msg = NULL;
	p->len = 0;
	p->prev = NULL;
	p->next = NULL;
}

static t_read	*new_link(t_read *current)
{
	if (!(current->next = (t_read *)ft_memalloc(sizeof(t_read))))
		return (NULL);
	init_read_struct(current->next);
	current->next->prev = current;
	return (current->next);
}

static int		fill_linked_list(t_read *origin, int fd)
{
	t_read	*current;
	int		r;
	int		n;
	char	buff[READ_BUFF_SIZE];

	n = 0;
	current = origin;
	while ((r = read(fd, buff, READ_BUFF_SIZE)) > 0)
	{
		if (!(current->msg = (char *)ft_memalloc(sizeof(char) * r)))
			return (-2);
		ft_memcpy(current->msg, buff, r);
		current->len = r;
		if (!(current = new_link(current)))
			return (-2);
		n += r;
	}
	if (fd)
		close(fd);
	if (r == -1
		&& ft_dprintf(2, "%sread error in ft_read [...]%s\n", KRED, KNRM))
		return (-1);
	return (n);
}

static void		merge_list(t_read *r, t_read *origin)
{
	t_read	*current;
	int		offset;

	current = origin;
	offset = 0;
	while (current->next)
	{
		ft_memcpy(r->msg + offset, current->msg, current->len);
		offset += current->len;
		current = current->next;
		free(current->prev->msg);
		if (current->prev != origin)
			free(current->prev);
	}
	free(current);
}

/*
** RETURN VALUE		SIGNIFICATION
**	 -2				malloc error
**	 -1				open/read error
**	  0				rien a lire
**	 >0				nombre de caractères lus
*/

int				ft_read(t_read *r, char *file)
{
	int		fd;
	t_read	origin;

	if (file == NULL)
		fd = 0;
	else
	{
		if ((fd = open(file, O_RDONLY)) == -1
			&& ft_dprintf(2, "%s\"%s\" is not a valid file for reading%s\n",
			KRED, file, KNRM))
			return (-1);
	}
	init_read_struct(r);
	init_read_struct(&origin);
	if ((r->len = fill_linked_list(&origin, fd)) <= 0)
		return (r->len);
	if (!(r->msg = (char *)ft_memalloc(sizeof(char) * (r->len + 1))))
		return (-2);
	merge_list(r, &origin);
	return (r->len);
}
