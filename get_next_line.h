#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

#endif
