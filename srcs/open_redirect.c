#include "../includes/minishell.h"

void ft_correct_rir(t_all *all) // ls >> 1.txt >> 2.txt >> 3.txt
{
    t_lst_pipe *tmp;
    t_lst_pipe *tmp_save;
    int save_reddirect;

    tmp = all->pipe;
    while(tmp->next)
    {
        tmp_save = tmp;
        save_reddirect = tmp->fd_redirect;
        while (tmp_save->f_red_pip == 2 && (tmp_save->next->f_red_pip == 2 || \
                    (tmp_save->prev && tmp_save->prev->f_red_pip == 2)) && tmp_save->fd_redirect != -1)
        {
            close(save_reddirect);
            save_reddirect = tmp_save->fd_redirect;
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
        printf("%s -- %i\n", tmp->command[0], tmp->fd_redirect);
        tmp = tmp->next;
    }
    exit(0);
    */
}

int ft_open_redirect(t_all *all)
{
    t_lst_pipe *tmp;

    tmp = all->pipe;
    while(tmp->next)
    {
        if (tmp->prev != NULL && tmp->prev->f_red_pip == 2) // >> and >
        {
            if (tmp->count_red_pip == 1)
                tmp->prev->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                tmp->prev->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
        } 
        if (tmp->prev != NULL && tmp->prev->f_red_pip == 3 && tmp->prev->count_red_pip == 1) // << and <
        {
            tmp->prev->fd_redirect = open(tmp->command[0], O_RDONLY, 0644);
        }
        tmp = tmp->next;
        if (errno != 0)
            return (errno);
    }
    ft_correct_rir(all);
    return(0);
}
