#include "../includes/minishell.h"


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

void	add_variable(t_env *env, char **arguments)
{
	int		word_count = 0;
	int		args_count = 0;
	int		i = 1;

	similar_var(env, arguments);

	while (*(env->envp + word_count))
		word_count++;
	while (*(arguments + i))
	{
		args_count++;
		i++;
	}
	env->envp = add_envp(env->envp, arguments, (word_count + args_count));
	env->var = add_var_val(env->var, arguments, (word_count + args_count), 0);
	env->val = add_var_val(env->val, arguments, (word_count + args_count), 1);
	env->f_equal = add_f_equal(env->envp, (word_count + args_count));
}

void	line_sort(char **envp)
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


int ft_export(t_env *env, char **arguments)
{
	char **sort_envp;
	char **sort_var;
	char **sort_val;
	int *f_equal;
	char **var_val;
	int i;

	i = 0;
	if (*(arguments + 1) != NULL)
	{
		add_variable(env, arguments);
	}
	else
	{
		sort_envp = arr_copy(env->envp);
		line_sort(sort_envp);
		while (sort_envp[i] != NULL)
			i++;
		sort_var = malloc(sizeof(char *) * (i + 1));
		sort_val = malloc(sizeof(char *) * (i + 1));
		f_equal = malloc(sizeof(int) * (i + 1));
		i = 0;
		while (sort_envp[i] != NULL) // сортировочка по алфавиту (заключить в кавычки все то что идет после знака равно!!!!)
		{
			if (ft_strchr(sort_envp[i], '='))
			{
				var_val = ft_split(sort_envp[i], '=');
				sort_var[i] = var_val[0];
				sort_val[i] = var_val[1];
				f_equal[i] = 2;
			}
			else
			{
				sort_var[i] = ft_strdup(sort_envp[i]);
				sort_val[i] = ft_strdup("");
				f_equal[i] = 1;
			}
			if (!var_val)
				free(var_val);
			i++;
		}
		i = 0;
		while (*(sort_envp + i))
		{
			if (ft_strncmp(sort_var[i], "?", ft_strlen("?")) != 0)
			{
				printf("declare -x %s", sort_var[i]);
				if (f_equal[i] == 2)
					printf("=\"%s\"", sort_val[i]);
				printf("\n");
			}
			i++;
		}
		free_arr(sort_envp);
	}
	return (0);
}
