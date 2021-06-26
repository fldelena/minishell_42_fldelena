#include "libft.h"

int	ft_endline(char *fullstr)
{
	int	i;

	i = 0;
	if (!fullstr)
		return (0);
	while (fullstr[i])
	{
		if (fullstr[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
