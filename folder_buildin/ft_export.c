#include "../includes/minishell.h"

void	add_variable(t_env *env, char **arguments)
{
	int		word_count;
	int		args_count;
	int		i;

	word_count = 0;
	args_count = 0;
	i = 1;
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
	int		count;
	int		i;
	int		j;

	count = 0;
	while (*(envp + count))
		count++;
	i = 1;
	while (i < count)
	{
		j = 0;
		while (j < count - i)
		{
			if (strcmp(*(envp + j), *(envp + j + 1)) > 0)
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

void	add_sort_env(t_env *sort, int i)
{
	char	**var_val;

	var_val = NULL;
	if (ft_strchr(sort->envp[i], '='))
	{
		var_val = ft_split(sort->envp[i], '=');
		sort->var[i] = var_val[0];
		sort->val[i] = var_val[1];
		sort->f_equal[i] = 2;
	}
	else
	{
		sort->var[i] = ft_strdup(sort->envp[i]);
		sort->val[i] = ft_strdup("");
		sort->f_equal[i] = 1;
	}
	if (!var_val)
		free(var_val);
}

void	sort_and_print(t_env *sort)
{
	int	i;

	i = 0;
	while (sort->envp[i] != NULL)
	{
		add_sort_env(sort, i);
		i++;
	}
	i = 0;
	while (*(sort->envp + i))
	{
		if (ft_strncmp(sort->var[i], "?", ft_strlen("?")) != 0)
		{
			printf("declare -x %s", sort->var[i]);
			if (sort->f_equal[i] == 2)
				printf("=\"%s\"", sort->val[i]);
			printf("\n");
		}
		i++;
	}
}

int	ft_export(t_all *all, char **arguments)
{
	t_env	*sort;
	int		i;

	i = 0;
	sort = (t_env *)malloc(sizeof(t_env));
	if (*(arguments + 1) != NULL)
		add_variable(all->env, arguments);
	else
	{
		sort->envp = arr_copy(all->env->envp);
		line_sort(sort->envp);
		while (sort->envp[i] != NULL)
			i++;
		sort->var = malloc(sizeof(char *) * (i + 1));
		sort->val = malloc(sizeof(char *) * (i + 1));
		sort->f_equal = malloc(sizeof(int) * (i + 1));
		sort_and_print(sort);
	}
	if (all->pipe->next != NULL)
		exit(0);
	return (0);
}
