/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khagiwar <khagiwar@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:56:21 by khagiwar          #+#    #+#             */
/*   Updated: 2020/11/02 13:56:23 by khagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>

typedef	enum {
	fail = -1,
	end = 0,
	success = 1,
	ln = 2
}	t_status;

int		get_next_line(int fd, char **line);
int		ft_strdiv(char **store, char *buf, char **line, ssize_t read_size);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
size_t	ft_strlen(const char *s, int c);
int		ft_strjoinln(char **s1, char *s2, char **line_break);
char	*ft_strln(const char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_close(char **store, char **line, char *buf, int status);

#endif
