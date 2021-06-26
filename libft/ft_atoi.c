#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	znak;
	long	out;

	i = 0;
	znak = 1;
	out = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			znak = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + str[i] - '0';
		i++;
	}
	return ((int)znak * out);
}
