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
		if (bytes <= 0)
			break;
		buffer[bytes] = '\0';
		if (!append_buffer(stash, buffer))
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (*stash);
}

static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + (stash[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*clean_stash(char *stash)
{
	size_t	i = 0;
	size_t	j = 0;
	char	*newstash;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	newstash = malloc(ft_strlen(stash) - i);
	if (!newstash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	while (stash[i])
		newstash[j++] = stash[i++];
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	stash = (void *)stash;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_and_append(fd, &stash))
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
