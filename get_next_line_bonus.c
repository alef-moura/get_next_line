/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesferr <alesferr@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 16:09:47 by alesferr          #+#    #+#             */
/*   Updated: 2026/07/15 14:56:03 by alesferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), free(stash), NULL);
		buf[bytes] = '\0';
		stash = ft_strjoin_free(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
	return (free(buf), stash);
}

static char	*extract_line(const char *stash)
{
	size_t	len;

	if (!stash || !*stash)
		return (NULL);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (ft_substr(stash, 0, len));
}

static char	*trim_stash(char *stash)
{
	char	*rest;
	char	*newline;

	newline = ft_strchr(stash, '\n');
	if (!newline || !*(newline + 1))
		return (free(stash), NULL);
	rest = ft_substr(newline + 1, 0, ft_strlen(newline + 1));
	return (free(stash), rest);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = trim_stash(stash[fd]);
	return (line);
}
