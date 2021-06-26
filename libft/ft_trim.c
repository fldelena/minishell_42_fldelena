#include "libft.h"

int	ft_trim(char *str)
{
	int	count;

	count = 0;
	while (str[count] == ' ')
		count++;
	return (count);
}
