#include "../includes/minishell.h"

void	ft_correct_rir(t_all *all)
{
	t_lst_pipe	*tmp;
	t_lst_pipe	*tmp_save;
	int			save_reddirect;

    /* tmp = all->pipe;
    // while(tmp->next)
    // {
    //     printf("%s -- %i  and flag_red_pip = %i\n", tmp->command[0], tmp->fd_redirect, tmp->f_red_pip);
    //     tmp = tmp->next;
    // }
    // printf("\n");
    */

	tmp = all->pipe;
	while (tmp->next)        // ls > a > b > c > d
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
    // tmp = all->pipe;
    // while(tmp->next)
    // {
    //     printf("%s -- %i  and flag_red_pip = %i\n", tmp->command[0], tmp->fd_redirect, tmp->f_red_pip);
    //     tmp = tmp->next;
    // }
    // exit(0);
    */
}

int	ft_open_redirect(t_all *all)
{
	t_lst_pipe	*tmp;

	tmp = all->pipe;
	while (tmp->next)
	{
		if (tmp->prev != NULL && (tmp->prev->f_red_pip == 2 \
			|| tmp->prev->f_red_pip == -10)) // >> and >
		{
			if (tmp->count_red_pip == 1)
			{
				tmp->prev->fd_redirect = \
					open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				tmp->f_red_pip = -10;
			}
			else
			{
				tmp->prev->fd_redirect = \
					open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
				tmp->f_red_pip = -10;
			}
		}
		if (tmp->prev != NULL && (tmp->prev->f_red_pip == 3 || tmp->prev->f_red_pip == -10) \
			&& tmp->prev->count_red_pip == 1) // << and <
		{
			tmp->prev->fd_redirect = open(tmp->command[0], O_RDONLY, 0644);
			tmp->f_red_pip = -10;
		}
		tmp = tmp->next;
		if (errno != 0)
			return (errno);
	}
	ft_correct_rir(all);
	return (0);
}
