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

int	ft_export(t_all *all, char **arguments)
{
	char	**sort_envp;
	char	**sort_var;
	char	**sort_val;
	int		*f_equal;
	char	**var_val;
	int		i;

	i = 0;
	if (*(arguments + 1) != NULL)
	{
		add_variable(all->env, arguments);
	}
	else
	{
		sort_envp = arr_copy(all->env->envp);
		line_sort(sort_envp);
		while (sort_envp[i] != NULL)
			i++;
		sort_var = malloc(sizeof(char *) * (i + 1));
		sort_val = malloc(sizeof(char *) * (i + 1));
		f_equal = malloc(sizeof(int) * (i + 1));
		i = 0;
		while (sort_envp[i] != NULL)
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
	if (all->pipe->next != NULL)
		exit(0);
	return (0);
}
