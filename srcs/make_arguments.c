#include "../includes/minishell.h"

char	*cut(char *arg, int *i)
{
	char	*str;
	char	quot;
	int		j;
	int		k;

	j = 0;
	k = *i;
	quot = arg[*i];
	while (arg[++k] != quot && arg[k - 1] != '\\' && arg[k] != '\0')
		j++;
	str = (char *)malloc(sizeof(char) * (j + 1));
	j = 0;
	while (arg[++(*i)] != quot && arg[(*i) - 1] != '\\' && arg[k] != '\0')
	{
		str[j] = arg[*i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*cut_quote(char *arg)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = (char *)malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg && arg[i])
	{
		if ((arg[i] == '"' || arg[i] == '\'')
			&& ((i > 0 && arg[i - 1] != '\\' ) || i == 0))
		{
			path = ft_strjoin(path, cut(arg, &i));
			j = ft_strlen(path);
			i++;
		}
		else if ((arg[i] == '"' || arg[i] == '\'')
			&& ((i > 0 && arg[i - 1] == '\\' ) || i == 0))
			j--;
		if ((arg[i] != '"' && arg[i] != '\''))
			path[j++] = arg[i++];
	}
	path[j] = '\0';
	return (path);
}
