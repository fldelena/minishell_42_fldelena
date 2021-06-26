#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*cpy;

	i = 0;
	cpy = (char *)malloc(ft_strlen(str) + 1);
	if (cpy == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
