/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:42:58 by ravard            #+#    #+#             */
/*   Updated: 2018/10/12 19:57:17 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		process_one(char *ptr, char *buf, char **line)
{
	int		len;
	char	*tmp;

	len = (*line) ? ft_strlen(*line) + ptr - buf + 1 : ptr - buf + 1;
	tmp = (char *)ft_memalloc(sizeof(char) * len);
	buf[ptr - buf] = '\0';
	if (*line)
	{
		ft_strcpy(tmp, *line);
		free(*line);
		ft_strcat(tmp, buf);
	}
	else
		ft_strcpy(tmp, buf);
	*line = tmp;
	ft_strncpy(buf, buf + (ptr - buf) + 1, BUFF_SIZE - (ptr - buf));
	return (1);
}

int		process_zero(char *buf, char **line)
{
	int		len;
	char	*tmp;

	len = (*line) ? ft_strlen(*line) + BUFF_SIZE + 1 : BUFF_SIZE + 1;
	tmp = (char *)ft_memalloc(sizeof(char) * len);
	if (*line)
	{
		ft_strcpy(tmp, *line);
		free(*line);
		ft_strcat(tmp, buf);
	}
	else
		ft_strcpy(tmp, buf);
	*line = tmp;
	buf[0] = '\0';
	return (0);
}

int		buf_process(char *buf, char **line)
{
	char	*ptr;

	if (buf[0] == '\0')
		return (0);
	if ((ptr = ft_strchr(buf, '\n')))
		return (process_one(ptr, buf, line));
	else
		return (process_zero(buf, line));
}

int		get_next_line(int fd, char **line)
{
	static char		*buf[MAX_FD + 1] = {NULL};
	int				ret;
	int				cond;

	if (fd == 1 || fd == 2 || fd < 0 || line == NULL)
		return (-1);
	*line = NULL;
	buf[fd] = (buf[fd] == NULL) ?
		(char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1)) : buf[fd];
	while (buf_process(buf[fd], line) != 1)
	{
		cond = (*line != NULL);
		if ((ret = read(fd, buf[fd], BUFF_SIZE)) == 0)
			return (cond);
		else if (ret == -1)
			return (-1);
		buf[fd][ret] = '\0';
	}
	return (1);
}
