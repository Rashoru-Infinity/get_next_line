/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khagiwar <khagiwar@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:55:53 by khagiwar          #+#    #+#             */
/*   Updated: 2020/11/02 13:55:55 by khagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdbool.h>

int		get_next_line(int fd, char **line)
{
	static char	*store;
	char		*buf;
	ssize_t		read_size;
	int			status;

	status = success;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ft_close(&store, line, NULL, fail));
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_close(&store, line, buf, fail));
	while ((read_size = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_size] = 0x1a;
		if ((status = ft_strdiv(&store, buf, line, read_size)) == ln)
			return (ft_close(&store, line, buf, ln));
		if (status == fail)
			return (ft_close(&store, line, buf, fail));
	}
	if (read_size < 0)
		status = fail;
	return (ft_close(&store, line, buf, status));
}

int		ft_strdiv(char **store, char *buf, char **line, ssize_t read_size)
{
	char	*line_break;

	if (read_size == 0)
		line_break = ft_strln(*store);
	else if (ft_strjoinln(store, buf, &line_break) == fail)
		return (ft_close(store, line, buf, fail));
	if (!line_break && read_size > 0)
		return (success);
	if (!(*line = (char *)malloc(sizeof(char) * (ft_strlen(*store, '\n') + 1))))
		return (ft_close(store, line, buf, fail));
	ft_memccpy(*line, *store, '\n', ft_strlen(*store, '\n'));
	(*line)[ft_strlen(*store, '\n')] = '\0';
	if (line_break)
	{
		ft_memmove(*store, &line_break[1], ft_strlen(&line_break[1], 0x1a) + 1);
		if (read_size > 0)
			return (ln);
		return (success);
	}
	if (read_size > 0)
		return (success);
	return (ft_close(store, line, buf, end));
}

int		ft_close(char **store, char **line, char *buf, int status)
{
	free(buf);
	if (status == ln)
		return (success);
	if (status == fail)
	{
		free(*store);
		*store = NULL;
		return (fail);
	}
	if (status == end)
	{
		free(*store);
		*store = NULL;
		return (end);
	}
	return (ft_strdiv(store, NULL, line, 0));
}
