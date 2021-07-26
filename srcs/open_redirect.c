#include "../includes/minishell.h"

void	ft_reddir_right(t_lst_pipe *tmp)
{
	if (tmp->count_red_pip == 1)
		tmp->prev->fd_redirect = \
			open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		tmp->prev->fd_redirect = \
			open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp->f_red_pip != 1)
		tmp->f_red_pip = -10;
	else
		tmp->f_red_pip = -1;
}

void	ft_red_left_one(t_lst_pipe *tmp)
{
	if (ft_strncmp(tmp->prev->command[0], "cat", \
			ft_strlen(tmp->prev->command[0])) == 0)
		ft_rewrite_arg_cat(tmp->prev);
	else
		tmp->prev->fd_redirect = open(tmp->command[0], \
			O_RDONLY, 0644);
}

void	ft_red_left_double(t_lst_pipe *tmp)
{
	char	*end_str;

	tmp->prev->fd_redirect = \
		open("name_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (TRUE)
	{
		end_str = readline("> ");
		if (ft_strncmp(end_str, tmp->command[0], ft_strlen(end_str)) == 0)
			break ;
		write(tmp->prev->fd_redirect, end_str, ft_strlen(end_str));
		write(tmp->prev->fd_redirect, "\n", ft_strlen("\n"));
		free(end_str);
	}
	free(end_str);
	if (ft_strncmp(tmp->prev->command[0], "cat", \
			ft_strlen(tmp->prev->command[0])) == 0)
		ft_two_red_arg_cat(tmp->prev);
}

void	ft_for_norm(t_lst_pipe *tmp)
{
	if (tmp->f_red_pip != 1)
		tmp->f_red_pip = -10;
	else
		tmp->f_red_pip = -1;
}

int	ft_open_redirect(t_all *all)
{
	t_lst_pipe	*tmp;

	tmp = all->pipe;
	while (tmp->next)
	{
		if (tmp->prev != NULL && \
			(tmp->prev->f_red_pip == 2 || tmp->prev->f_red_pip == -10))
			ft_reddir_right(tmp);
		if (tmp->prev != NULL && (tmp->prev->f_red_pip == 3))
		{
			if (tmp->count_red_pip == 1)
				ft_red_left_one(tmp);
			else
				ft_red_left_double(tmp);
			ft_for_norm(tmp);
		}
		if (errno != 0)
		{
			printf("minishell: %s: %s\n", tmp->command[0], strerror(errno));
			return (errno);
		}
		tmp = tmp->next;
	}
	ft_correct_rir(all);
	return (0);
}
