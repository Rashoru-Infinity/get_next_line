/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khagiwar <khagiwar@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:55:53 by khagiwar          #+#    #+#             */
/*   Updated: 2020/11/13 22:53:17 by khagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <stdbool.h>

void	remove_list(int fd, t_list **head, t_list *prev)
{
	t_list *curr;

	if (!head)
		return ;
	curr = *head;
	if (curr->fd == fd)
	{
		if (prev)
			prev->next = curr->next;
		else
			*head = curr->next;
		free(curr->str);
		free(curr);
	}
	else if (curr->next)
		remove_list(fd, &(curr->next), curr);
}

t_list	*get_list(int fd, t_list **head)
{
	t_list *curr;

	curr = *head;
	if (!curr)
	{
		if (!(curr = (t_list *)malloc(sizeof(t_list))))
			return (NULL);
		*curr = (t_list){NULL, NULL, fd};
		*head = curr;
	}
	while (curr)
	{
		if (curr->fd == fd)
			return (curr);
		if (!(curr->next))
		{
			if (!(curr->next = (t_list *)malloc(sizeof(t_list))))
				break ;
			*(curr->next) = (t_list){NULL, NULL, fd};
		}
		curr = curr->next;
	}
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*store;
	t_scanner		in;
	int				status;
	t_list			*curr;

	status = success;
	in.fd = fd;
	in.buf = NULL;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (ft_close(&store, line, &in, fail));
	if (!(curr = get_list(fd, &store)))
		return (ft_close(&store, line, &in, fail));
	if (!(in.buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_close(&store, line, &in, fail));
	while ((in.rdsz = read(fd, in.buf, BUFFER_SIZE)) > 0)
	{
		in.buf[in.rdsz] = 0x1a;
		if ((status = ft_strdiv(&store, &in, line)) == ln)
			return (ft_close(&store, line, &in, ln));
		if (status == fail)
			return (ft_close(&store, line, &in, fail));
	}
	if (in.rdsz < 0)
		status = fail;
	return (ft_close(&store, line, &in, status));
}

int		ft_strdiv(t_list **store, t_scanner *in, char **line)
{
	char	*line_break;
	t_list	*lst;

	lst = get_list(in->fd, store);
	if (in->rdsz == 0)
		line_break = ft_strln(lst->str);
	else if (ft_strjoinln(&(lst->str), in->buf, &line_break) == fail)
		return (ft_close(store, line, in, fail));
	if (!line_break && in->rdsz > 0)
		return (success);
	if (!(*line = (char *)malloc(sizeof(char) *
	(ft_strlen(lst->str, '\n') + 1))))
		return (ft_close(store, line, in, fail));
	ft_memccpy(*line, lst->str, '\n', ft_strlen(lst->str, '\n'));
	(*line)[ft_strlen(lst->str, '\n')] = '\0';
	if (line_break)
	{
		ft_memmove(lst->str, &line_break[1],
		ft_strlen(&line_break[1], 0x1a) + 1);
		if (in->rdsz > 0)
			return (ln);
		return (success);
	}
	return (ft_close(store, line, in, end));
}

int		ft_close(t_list **store, char **line, t_scanner *in, int status)
{
	free(in->buf);
	(*in).buf = NULL;
	if (status == ln)
		return (success);
	if (status == fail || status == end)
	{
		remove_list(in->fd, store, NULL);
		return (status);
	}
	(*in).rdsz = 0;
	return (ft_strdiv(store, in, line));
}
