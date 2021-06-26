#include "../includes/minishell.h"

int		is_n_flag(char *s)
{
	int i = 0;
	while (s[++i])
	{
		if (s[i] != 'n' || s[0] != '-')
			return (0);
	}
	if (ft_strlen(s) == 1)
		return (0);
	return (1);
}


// void	**line_sort(char **arg)                            попытался отсортировать строки по алфавиту, доделаю !
// {
// 	char	*str;
// 	int		count = 0;
// 	int		i = 1;
// 	int		j;

// 	while (*(envp + count))
// 		count++;
// 	while (i < count)
// 	{
// 		j = 0;
// 		while (j < count - i)
// 		{
// 			if(strcmp(*(envp + j), *(envp + j + 1)) > 0)
// 			{
// 				str = ft_substr(*(envp + j));
// 				ft_strcpy(*(envp + j), *(envp + j + 1));
// 				ft_strcpy(*(envp + j + 1), str);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
