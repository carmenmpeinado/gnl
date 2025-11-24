#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (0);
	while (str[n])
		n++;
	return (n);
}

char	*ft_strdup(char *s)
{
	char	*newstr;
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	newstr = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (s[i] != '\0')
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	char	*substr;
	size_t	total_len;
	size_t	i;

	if (!s)
		return (NULL);
	total_len = ft_strlen(s);
	if (start >= total_len)
		return (ft_strdup(""));
	if (start + n > total_len)
		n = total_len - start;
	substr = malloc(sizeof(char) * (n + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < n && s[start + i])
	{
		substr[i] = s[start + i];
		i ++;
	}
	substr[i] = '\0';
	return (substr);
}
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*joined;
	size_t	len1;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	joined = malloc (len1 + ft_strlen(s2) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		joined[len1] = s2[i];
		len1++;
		i++;
	}
	joined[len1] = '\0';
	return (joined);
}
char *ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
