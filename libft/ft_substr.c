#include "libft.h"

char	*ft_substr(char *s)
{
	char *str;
	int i;

	if (!s)
		return(NULL);
	i = -1;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (++i < ft_strlen(s) && *(s + i))
		*(str + i) = *(s + i);
	*(str + i) = '\0';
	return (str);
}
