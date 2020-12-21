/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khagiwar <khagiwar@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 10:13:01 by khagiwar          #+#    #+#             */
/*   Updated: 2020/11/13 22:53:55 by khagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <stdbool.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	size_t	offset;
	bool	found;

	i = 0;
	offset = 0;
	found = false;
	while (i < n)
	{
		if (*(char *)(src + i) == 0x1a)
			break ;
		if (!found)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		if (*(unsigned char *)(dest + i) == (unsigned char)c && !found)
		{
			offset = ++i;
			found = true;
			break ;
		}
		++i;
	}
	if (found)
		return (dest + offset);
	return (NULL);
}

size_t	ft_strlen(const char *s, int c)
{
	size_t offset;

	if (!s)
		return (0);
	offset = 0;
	while (s[offset] != 0x1a)
	{
		if (s[offset] == c)
			break ;
		++offset;
	}
	return (offset);
}

int		ft_strjoinln(char **s1, char *s2, char **line_break)
{
	char	*str;
	size_t	offset1;
	size_t	offset2;

	if (!s1 || !(str = (char *)malloc(sizeof(char) *
	(ft_strlen(*s1, 0x1a) + ft_strlen(s2, 0x1a) + 1))))
		return (fail);
	offset1 = 0;
	while (s1 && *s1 && (*s1)[offset1] != 0x1a)
	{
		str[offset1] = (*s1)[offset1];
		++offset1;
	}
	offset2 = 0;
	while (s2 && s2[offset2] != 0x1a)
	{
		str[offset1 + offset2] = s2[offset2];
		++offset2;
	}
	str[offset1 + offset2] = 0x1a;
	if (s1)
		free(*s1);
	*s1 = str;
	*line_break = ft_strln(*s1);
	return (success);
}

char	*ft_strln(const char *s)
{
	size_t offset;

	if (!s)
		return (NULL);
	offset = 0;
	while (s[offset] != 0x1a)
	{
		if (s[offset] == '\n')
			return ((char *)&s[offset]);
		++offset;
	}
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t i;
	size_t offset;

	if (!dest && !src)
		return (NULL);
	i = 0;
	offset = 0;
	while (i < n)
	{
		if (dest > src)
			offset = n - i - 1;
		else
			offset = i;
		*(char *)(dest + offset) = *(char *)(src + offset);
		if (*(char *)(src + offset) == 0x1a)
			break ;
		++i;
	}
	return (dest);
}
