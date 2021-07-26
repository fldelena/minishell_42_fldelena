#include "../includes/minishell.h"

void	ft_correct_rir(t_all *all)
{
	t_lst_pipe	*tmp;
	t_lst_pipe	*tmp_save;
	int			save_reddirect;

	tmp = all->pipe;
	while (tmp->next)
	{
		tmp_save = tmp;
		save_reddirect = tmp->fd_redirect;
		while ((tmp_save->f_red_pip == 2 || tmp_save->f_red_pip == -10) \
			&& (tmp_save->next->f_red_pip == 2 \
			|| tmp_save->next->f_red_pip == -10) && tmp_save->fd_redirect != -1)
		{
			if (tmp_save->next->next && tmp_save->next->next->f_red_pip == -10)
			{
				close(save_reddirect);
				save_reddirect = tmp_save->next->fd_redirect;
			}
			tmp_save->fd_redirect = -1;
			tmp_save = tmp_save->next;
		}
		tmp->fd_redirect = save_reddirect;
		tmp = tmp->next;
	}
}

void	ft_rewrite_arg_cat(t_lst_pipe *tmp)
{
	int		i;
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
	int		i;
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
