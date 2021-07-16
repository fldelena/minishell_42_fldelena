#include "libft.h"

static int		size_n(int a)
{
	int		size;
	int		b;

	b = a;
	size = 1;
	if (a < 0)
		size++;
	while ((b /= 10) != 0)
		size++;
	return (size);
}

static int		sign_n(int a)
{
	if (a < 0)
		return (-1);
	return (1);
}

char			*ft_itoa(int a)
{
	int		size;
	int		sign;
	int		b;
	char	*str;
	int		j;

	j = 0;
	size = size_n(a);
	sign = sign_n(a);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	if (a < 0)
	{
		str[0] = '-';
		j = 1;
	}
	b = a;
	while (--size >= j)
	{
		str[size] = (b % 10) * sign + '0';
		b /= 10;
	}
	return (str);
}
