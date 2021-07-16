#include "libft.h"

size_t	ft_strcpy(char *dst, char *src)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
