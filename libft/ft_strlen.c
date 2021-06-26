#include "libft.h"

size_t	ft_strlen(const char *array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
