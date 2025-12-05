/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: capeinad <capeinad@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 23:07:43 by capeinad          #+#    #+#             */
/*   Updated: 2025/11/29 00:02:13 by capeinad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int	check_init_errors(char **stash)
{
	if (!*stash)
	{
		*stash = ft_strdup("");
		if (!*stash)
			return (0);
	}
	return (1);
}

static int	append_buffer(char **stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(*stash, buffer);
	if (!tmp)
	{
		free(*stash);
		*stash = NULL;
		return (0);
	}
	free(*stash);
	*stash = tmp;
	return (1);
}

static char	*read_and_append(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytes;

	if (!check_init_errors(stash))
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(*stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			break ;
		buffer[bytes] = '\0';
		if (!append_buffer(stash, buffer))
			return (free(buffer), NULL);
	}
	free(buffer);
	if (*stash && (*stash)[0] == 0)
	{
		free(*stash);
		*stash = NULL;
	}
	return (*stash);
}

static char	*extract_line(char **stash)
{
	size_t	i;
	char	*line;
	char	*rest;

	if (!**stash || !*stash)
		return (NULL);
	i = 0;
	line = NULL;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
	{
		line = ft_substr(*stash, 0, i + 1);
		rest = ft_substr(*stash, i + 1, (ft_strlen(*stash) - (i + 1)));
		free(*stash);
		*stash = rest;
	}
	else if ((*stash)[i] == '\0')
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_and_append(fd, &stash))
		return (NULL);
	line = extract_line(&stash);
	return (line);
}
