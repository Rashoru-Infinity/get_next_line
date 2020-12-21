/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khagiwar <khagiwar@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:56:21 by khagiwar          #+#    #+#             */
/*   Updated: 2020/11/13 22:55:21 by khagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>

typedef	enum {
	fail = -1,
	end = 0,
	success = 1,
	ln = 2
}	t_status;

typedef struct	s_list {
	struct s_list	*next;
	char			*str;
	int				fd;
}				t_list;

typedef struct	s_scanner {
	char	*buf;
	int		fd;
	ssize_t	rdsz;
}				t_scanner;

void			remove_list(int fd, t_list **head, t_list *prev);
int				get_next_line(int fd, char **line);
int				ft_strdiv(t_list **store, t_scanner *in, char **line);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
size_t			ft_strlen(const char *s, int c);
int				ft_strjoinln(char **s1, char *s2, char **line_break);
char			*ft_strln(const char *s);
void			*ft_memmove(void *dest, const void *src, size_t n);
int				ft_close(t_list **store, char **line,
				t_scanner *in, int status);

#endif
