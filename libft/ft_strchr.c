#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i++;
	}
	if (!ch && str[i] == '\0')
		return ((char *)str + i);
	return (NULL);
}
