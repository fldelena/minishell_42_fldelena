#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(len + 1);
	if (!join)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		join[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	join[i] = '\0';
	free((char *)s1);
	return (join);
}
