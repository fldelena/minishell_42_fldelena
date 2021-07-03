#include "../includes/minishell.h"

char	**arr_copy(char **envp)				// функция копирующая массив строк
{
	char	**my_envp;
	int i;

	i = 0;
	while (*(envp + i))
		i++;
	my_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*(envp + i))
	{
		my_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	my_envp[i] = NULL;
	return(my_envp);
}

int		is_n_flag(char *s)					// функция для корректной работы -n в echo
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


void	line_sort(char **envp)				// сортирует строки в алфавитном порядке для export
{
	char	*str;
	int		count = 0;
	int		i = 1;
	int		j;

	while (*(envp + count))
		count++;
	while (i < count)
	{
		j = 0;
		while (j < count - i)
		{
			if(strcmp(*(envp + j), *(envp + j + 1)) > 0)
			{
				str = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = str;
			}
			j++;
		}
		i++;
	}
}

char	**add_variable(char **arr, char **arguments) // добавляет наши переменные окружения в массив
{
	char	**str;
	int		word_count = 0;
	int		args_count = 0;
	int		i = 1;						// почему 1 ? да потому что первый аргумент "export"
	int		j = 1;						// почему тут тоже 1 ? причина та же самая

	while (*(arr + word_count))
		word_count++;					// тут я храню количество строк в массиве
	while (*(arguments + i))
	{
		args_count++;					// а тут количество аргументов которые мы подаем
		i++;
	}
	str = malloc(word_count + args_count + 1);	//  1 для NULL
	i = 0;
	while (*(arr + i))
	{
		str[i] = arr[i];
		i++;
	}
	while (*(arguments + j))
	{
		str[i] = arguments[j];
		i++;
		j++;
	}
	str[i] = NULL;
	// free_arr(arr);            // вот благодаря этой суке у меня не выводится 0,1,2,9 строки
	return (str);
}


char	**del_variable(t_env *env, char **arguments)
{
	char	**str;
	int		word_count = 0;
	int		args_count = 0;
	int		i = 1;
	int		j;
	int		k;

	while (env->envp[word_count])
		word_count++;
	while (*(arguments + i))
	{
		args_count++;					// а тут количество аргументов которые мы подаем
		i++;
	}
	str = malloc(word_count - args_count + 1);
	i = 0;
	k = 0;
	while(env->envp[i])
	{
		j = 1;
		while(*(arguments + i))
		{
			if(strcmp(env->var[i], *(arguments + i)))
			{
				i++;
				continue ;
			}
			j++;
		}
		str[k] = arguments[i];
		i++;
		k++;
	}
	str[k] = NULL;
	return (str);
}

void	make_envp(t_all *all, char **envp)
{
	char **arr;
	int i;

	i = 0;
	while (envp[i])
	{
		all->env->envp[i] = strdup(*(envp + i)); // при полной работе цикла первые строки масива
		// printf("%s\n", all->env->envp[i]);
		arr = ft_split(*(envp + i), '=');
		all->env->var[i] = arr[0];
		all->env->val[i] = arr[1];
		// free(arr);
		i++;
	}
	// printf("count: %d\n", i);
	all->env->envp[i] = NULL;
	all->env->var[i] = NULL;
	all->env->val[i] = NULL;
	// i = 0;
	// while(all->env->envp[i] != NULL)
	// {
	// 	printf("%s\n", all->env->envp[i]);
	// 	i++;
	// }
	// printf("count2: %d\n", i);
}
