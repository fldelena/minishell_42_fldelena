#include "libft.h"

static unsigned int	indx_srch(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int				i;
	unsigned int	size_str;
	char			*start_str;
	char			*end_str;
	char			*outstr;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && indx_srch(s1[i], set))
		i++;
	start_str = (char *)&s1[i];
	i = ft_strlen(s1) - 1;
	if (i != -1)
		while (i >= 0 && indx_srch(s1[i], set))
			i--;
	end_str = (char *)&s1[i];
	if (!*s1 || end_str == start_str)
		size_str = 2;
	else
		size_str = end_str - start_str + 2;
	outstr = malloc(sizeof(char) * size_str);
	ft_strlcpy(outstr, start_str, size_str);
	free(s1);
	return (outstr);
}
