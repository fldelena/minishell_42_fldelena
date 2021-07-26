#include "../includes/minishell.h"

t_lst_pipe	*ft_find_num(t_all *all, int *count, int num)
{
	t_lst_pipe	*tmp;

	tmp = all->pipe;
	while (tmp->next)
	{
		if (tmp->num == num)
			break ;
		tmp = tmp->next;
	}
	*count = tmp->start_arg;
	return (tmp);
}

int	ft_count_last_lst(char **arguments, int count)
{
	int	i;

	i = 0;
	while (arguments[count])
	{
		count++;
		i++;
	}
	count = i;
	return (count);
}

int	ft_make_help(t_all *all, char **arguments, int *count, int num)
{
	t_lst_pipe	*tmp_help;
	t_lst_pipe	*tmp;
	int			count_tmp_arg;

	count_tmp_arg = 0;
	tmp = all->pipe;
	tmp = ft_find_num(all, count, num);
	tmp_help = tmp->next;
	if (tmp->next && tmp_help->next)
	{
		tmp = tmp->next;
		(*count) = tmp->start_arg - (*count);
	}
	else
		(*count) = ft_count_last_lst(arguments, (*count));
	if (tmp->prev && tmp->next && tmp_help->next)
	{
		tmp = tmp->prev;
		count_tmp_arg = tmp->start_arg;
	}
	else
		count_tmp_arg = tmp->start_arg;
	return (count_tmp_arg);
}

char	**ft_make_arg_n(char **arguments, t_all *all, int num)
{
	int			count;
	int			count_tmp_arg;
	int			i;
	char		**arg_now;
	t_lst_pipe	*tmp;

	count_tmp_arg = 0;
	tmp = all->pipe;
	if (num != 0)
		count_tmp_arg = ft_make_help(all, arguments, &count, num);
	else
		count = tmp->next->start_arg;
	arg_now = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i != count)
	{
		arg_now[i] = arguments[i + count_tmp_arg];
		i++;
	}
	arg_now[i] = NULL;
	return (arg_now);
}

int	ft_work_old(char **arg_now, t_all *all)
{
	if (!arg_now[0])
		return (0);
	if (ft_strncmp(arg_now[0], "pwd", ft_strlen("pwd")) == 0)
	{
		printf("%s\n", getcwd(0, 0));
		if (all->pipe->next != NULL)
			exit(0);
		return (errno);
	}
	else if (ft_strncmp(arg_now[0], "echo", ft_strlen("echo")) == 0)
		return (ft_echo(all, 1, arg_now));
	else if (ft_strncmp(arg_now[0], "cd", ft_strlen("cd")) == 0)
		return (ft_cd(arg_now, all));
	else if (ft_strncmp(arg_now[0], "env", ft_strlen("env")) == 0)
		return (ft_env(all));
	else if (ft_strncmp(arg_now[0], "export", ft_strlen("export")) == 0)
		return (ft_export(all, arg_now));
	else if (ft_strncmp(arg_now[0], "unset", ft_strlen("unset")) == 0)
		return (ft_unset(all, arg_now));
	else if (ft_strncmp(arg_now[0], "exit", ft_strlen("exit")) == 0)
		ft_exit(arg_now);
	else
		return (binary_work(all, arg_now));
	return (127);
}
