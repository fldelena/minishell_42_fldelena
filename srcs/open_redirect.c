#include "../includes/minishell.h"

void	ft_correct_rir(t_all *all)
{
	t_lst_pipe	*tmp;
	t_lst_pipe	*tmp_save;
	int			save_reddirect;

    /*
	tmp = all->pipe;
    while(tmp->next)
    {
        printf("%s -- %i  and flag_red_pip = %i\n", tmp->command[0], tmp->fd_redirect, tmp->f_red_pip);
        tmp = tmp->next;
    }
    printf("\n");
    */
	tmp = all->pipe;
	while (tmp->next)        // ls > a | ls > b
	{
		tmp_save = tmp;
		save_reddirect = tmp->fd_redirect;
		while ((tmp_save->f_red_pip == 2 || tmp_save->f_red_pip == -10) && (tmp_save->next->f_red_pip == 2 \
			|| tmp_save->next->f_red_pip == -10) && tmp_save->fd_redirect != -1)
		{
			if (tmp_save->next->next && tmp_save->next->next->f_red_pip == -10)
			{
				// printf("          +         fd_redirect close = %i\n", save_reddirect);
				close(save_reddirect);
				save_reddirect = tmp_save->next->fd_redirect;
			}
			tmp_save->fd_redirect = -1;
			tmp_save = tmp_save->next;
		}
		tmp->fd_redirect = save_reddirect;
		tmp = tmp->next;
	}
    /*
    tmp = all->pipe;
    while(tmp->next)
    {
        printf("%s -- %i  and flag_red_pip = %i\n", tmp->command[0], tmp->fd_redirect, tmp->f_red_pip);
        tmp = tmp->next;
    }
    exit(0);
    */
}

void	ft_rewrite_arg_cat(t_lst_pipe *tmp)
{
	int 	i;
	int		j;
	char	**new_com;

	i = 0;
	j = 0;
	while (tmp->command[i] != NULL)
		i++;
	new_com = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp->command[i] != NULL)
	{
		new_com[i] = tmp->command[i];
		i++;
	}
	while (tmp->next->command[j] != NULL)
		j++;
	new_com[i] = ft_strdup(tmp->next->command[j - 1]);
	new_com[i + 1] = NULL;
	free(tmp->command);
	tmp->command = new_com;
}

void	ft_two_red_arg_cat(t_lst_pipe *tmp)
{
	int 	i;
	char	**new_com;

	i = 0;
	while (tmp->command[i] != NULL)
		i++;
	new_com = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp->command[i] != NULL)
	{
		new_com[i] = tmp->command[i];
		i++;
	}
	new_com[i] = ft_strdup("name_tmp\0");
	new_com[i + 1] = NULL;
	free(tmp->command);
	tmp->command = new_com;
}

int	ft_open_redirect(t_all *all)
{
	t_lst_pipe	*tmp;

	tmp = all->pipe;
	while (tmp->next)
	{
		if (tmp->prev != NULL && \
			(tmp->prev->f_red_pip == 2 || tmp->prev->f_red_pip == -10))
		{
			if (tmp->count_red_pip == 1)
				tmp->prev->fd_redirect = \
					open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				tmp->prev->fd_redirect = \
					open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp->f_red_pip != 1)		// вынести ещё ниже тк повторяется
				tmp->f_red_pip = -10;
			else
				tmp->f_red_pip = -1;
		}
		if (tmp->prev != NULL && (tmp->prev->f_red_pip == 3))
		{
			if (tmp->count_red_pip == 1)
			{
				if (ft_strncmp(tmp->prev->command[0], "cat", ft_strlen(tmp->prev->command[0])) == 0)
					ft_rewrite_arg_cat(tmp->prev);
				else
					tmp->prev->fd_redirect = open(tmp->command[0], O_RDONLY, 0644);
			}
			else
			{
				tmp->prev->fd_redirect = open("name_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				char *end_str;
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
				if (ft_strncmp(tmp->prev->command[0], "cat", ft_strlen(tmp->prev->command[0])) == 0)
					ft_two_red_arg_cat(tmp->prev);
			}
			if (tmp->f_red_pip != 1)
				tmp->f_red_pip = -10;
			else
				tmp->f_red_pip = -1;
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
