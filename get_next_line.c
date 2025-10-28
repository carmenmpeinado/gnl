
#include "get_next_line.h"
#include <stddef.h>


static size_t	findnewline(const char *s)
{
	size_t	i;

	if (!s)
		return((size_t)-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return ((size_t)-1);
}

static char	*joinfree(char *s1, const char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (s1)
		len1 = ft_strlen(s1);
	else
	 	len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	joined = malloc(len1 + len2 +1);
	if (!joined)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(joined, s1, len1 +1);
		free(s1);
	}
	else
		joined[0] = '\0';
	ft_strlcat(joined, s2, len1 + len2 +1);
	return (joined);
}

static char	*linegiven(char *buffered)
{
	size_t	position;
	char	*line;

	if(!buffered || !*buffered)
		return (NULL);
	position = findnewline(buffered);
	if (position == (size_t)-1)
		position = ft_strlen(buffered);
	line = malloc(position + 2);
	if(!line)
		return (NULL);
	ft_strlcpy(line, buffered, position +2);
	return (line);
}

static char	*clean(char *buffered)
{
	size_t	position;
	size_t	len;
	char	*renew;

	position = findnewline(buffered);
	if (position == (size_t)-1)
	{
		free(buffered);
		return(NULL);
	}
	len = ft_strlen(buffered + position +1);
	renew = malloc(len+1);
	if (!renew)
		return(NULL);
	ft_strlcpy(renew, buffered + position +1, len +1);
	free(buffered);
	return(renew);
}
char	*get_next_line(int fd)
{
	char	*line;
	static char	*buffered;
	char	stockage[BUFFER_SIZE +1];
	size_t	bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (findnewline(buffered) == (size_t)-1 && bytes > 0)
	{
		bytes = read(fd, stockage, BUFFER_SIZE);
		if (bytes <= 0)
			break;
		stockage[bytes] = '\0';
		buffered = joinfree(buffered, stockage);
		if (!buffered)
			return(NULL);
	}
	line = linegiven(buffered);
	buffered = clean(buffered);
	return(line);
}
