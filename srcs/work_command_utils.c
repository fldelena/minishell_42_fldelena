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

char **add_envp(char **envp, char **arguments, int words)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc(sizeof(char *) * (words + 1));
	i = 0;
	while (*(envp + i))
	{
		new_envp[i] = envp[i];
		i++;
	}
	j = 1;
	while (*(arguments + j))
	{
		new_envp[i] = ft_strdup(arguments[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char **add_var_val(char **arr, char **arguments, int words, int index)
{
	char	**var_val;
	char	**src;
	int		i;
	int		j;

	var_val = malloc(sizeof(char *) * (words + 1));
	i = 0;
	while (*(arr + i))
	{
		var_val[i] = arr[i];
		i++;
	}
	j = 1;
	while (*(arguments + j))
	{
		if (ft_strchr(*(arguments + j), '='))
		{
			src = ft_split(*(arguments + j), '=');
			var_val[i] = ft_strdup(src[index]);
			free_arr(src);
		}
		else
		{
			if (index == 0)
				var_val[i] = ft_strdup(arguments[j]);
			else
				var_val[i] = ft_strdup("");
		}
		i++;
		j++;
	}
	var_val[i] = NULL;
	return (var_val);
}

int		*add_f_equal(char **envp, int words)
{
	int *arr;
	int i;

	i = 0;
	arr = malloc(sizeof(int) * words + 1);
	while (envp[i] != '\0')
	{
		if (ft_strchr(envp[i], '='))
			arr[i] = 2;
		else
			arr[i] = 1;
		i++;
	}
	arr[i] = '\0';
	return(arr);
}

char	**del_by_index(char **src, int index)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i] != NULL)
		i++;
	arr = malloc(sizeof(char *) * i); // не прибавляю единичку так как мне нужно на один элемент массива меньше чем было
	i = 0;
	while (src[i] != NULL)
	{
		if (i == index)
			i++;
		arr[j] = src[i];
		if (arr[j] == NULL)
		{
			free (src);
			return (arr);
		}
		j++;
		i++;
	}
	arr[j] = NULL;
	free (src);
	return (arr);
}

int		*del_int_by_index(int *src, int index)
{
	int *arr;
	int i;
	int j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	arr = malloc(sizeof(int) * i);
	i = 0;
	while (src[i] != '\0')
	{
		if (i == index)
			i++;
		arr[j] = src[i];
		if (arr[j] == '\0')
		{
			free (src);
			return (arr);
		}
		j++;
		i++;
	}
	arr[j] = '\0';
	free (src);
	return (arr);
}

void	del_similar_var(t_env *env, int index)
{
	env->envp = del_by_index(env->envp, index);
	env->var = del_by_index(env->var, index);
	env->val = del_by_index(env->val, index);
	env->f_equal = del_int_by_index(env->f_equal, index);
}

void	similar_var(t_env *env, char **arguments)
{
	int i;
	int j;

	i = 0;
	while(env->var[i])
	{
		j = 1;
		while(arguments[j])
		{
			if (ft_strncmp(env->var[i], arguments[j], ft_strlen(env->var[i])) == 0)
			{
				del_similar_var(env, i);
				i--;
			}
			j++;
		}
		i++;
	}
}

void	add_variable(t_env *env, char **arguments) // добавляет наши переменные окружения в массив
{
	int		word_count = 0;
	int		args_count = 0;
	int		i = 1;						// почему 1 ? да потому что первый аргумент "export"

	similar_var(env, arguments);		// функция отвечает за то, чтобы переменные не повторялись

	while (*(env->envp + word_count))
		word_count++;					// тут я храню количество строк в массиве
	while (*(arguments + i))
	{
		args_count++;					// а тут количество аргументов которые мы подаем
		i++;
	}
	env->envp = add_envp(env->envp, arguments, (word_count + args_count));
	env->var = add_var_val(env->var, arguments, (word_count + args_count), 0);
	env->val = add_var_val(env->val, arguments, (word_count + args_count), 1);
	env->f_equal = add_f_equal(env->envp, (word_count + args_count));
}

char	**del(char **var, char **envp, char **arguments, int words)
{
	char	**new_envp;
	int		i;
	int		j;
	int		k;

	new_envp = malloc(sizeof(char *) * (words + 1));
	i = 0;
	k = 0;
	while (envp[i] != NULL)
	{
		j = 1;
		while (arguments[j] != NULL)
		{
			if (strcmp(var[i], arguments[j]) == 0)
			{
					i++;
			}
			j++;
		}
		new_envp[k] = envp[i];
		if (new_envp[k] == NULL)
			return (new_envp);
		k++;
		i++;
	}
	new_envp[k] = NULL;
	return (new_envp);
}

int		*del_f_equal(t_env *env, char **arguments, int words)
{
	int		*arr;
	int		i;
	int		j;
	int		k;

	arr = malloc(sizeof(int) * (words + 1));
	i = 0;
	k = 0;
	while (env->envp[i] != NULL)
	{
		j = 1;
		while (arguments[j] != NULL)
		{
			if (strcmp(env->var[i], arguments[j]) == 0)
					i++;
			j++;
		}
		if (ft_strchr(env->envp[i], '='))
			arr[k] = 2;
		else
			arr[k] = 1;
		if(env->envp[i] == NULL)
		{
			arr[k] = '\0';
			return (arr);
		}
		i++;
		k++;
	}
	arr[k] = '\0';
	return(arr);
}

void	del_variable(t_env *env, char **arguments)
{
	int		word_count = 0;
	int		args_count = 0;
	int		i = 1;

	while (env->envp[word_count])
		word_count++;
	while (*(arguments + i))
	{
		args_count++;
		i++;
	}
	env->envp = del(env->var, env->envp, arguments, (word_count - args_count));
	env->val = del(env->var, env->val, arguments, (word_count - args_count));
	env->var = del(env->var, env->var, arguments, (word_count - args_count));
	env->f_equal = del_f_equal(env, arguments, (word_count - args_count));
}

void	make_envp(t_all *all, char **envp)
{
	char	**arr;
	int		i;

	i = 0;
	while (envp[i])
	{
		all->env->envp[i] = ft_strdup(*(envp + i));
		if(ft_strchr(all->env->envp[i], '='))
		{
			all->env->f_equal[i] = 2;
			arr = ft_split(*(envp + i), '=');
			all->env->var[i] = ft_strdup(arr[0]);
			all->env->val[i] = ft_strdup(arr[1]);
		}
		else
		{
			all->env->f_equal[i] = 1;
			all->env->var[i] = ft_strdup(*(envp + i));
			all->env->val[i] = ft_strdup("");
		}
		free_arr(arr);
		i++;
	}
	all->env->envp[i] = NULL;
	all->env->var[i] = NULL;
	all->env->val[i] = NULL;
	all->env->f_equal[i] = '\0';
}
