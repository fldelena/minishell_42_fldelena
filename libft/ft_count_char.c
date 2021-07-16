#include "libft.h"

int	ft_count_char(char *str, char c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(str[i] != '\0')
	{
		if ((i == 0 && str[i] == c) || (str[i] == c && str[i - 1] != '\\'))
			count++;
		i++;
	}
	return (count);
}
