#include "../includes/minishell.h"

int ft_open_redirect(t_all *all)
{
    (void)all;
    return (0);
    // t_lst_pipe *tmp;

    // tmp = all->pipe;        // ls | cat -e >> 1.txt >> 2.txt
    // while(tmp->next)
    // {
    //     if (tmp->prev != NULL && tmp->prev->f_red_pip == 2) // если сейчас название файла, но не команда
    //     {
    //         if (tmp->count_red_pip == 1)
    //             tmp->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //         else
    //             tmp->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    //     }
    //     // первое слово должно быть командой  (считываем пока не появится символ l)   или ls < 1.txt
    //     if (tmp->prev != NULL && tmp->prev->f_red_pip == 3) // если сейчас название файла, но не команда
    //     {
    //         tmp->fd_redirect = open(tmp->command[0], O_RDONLY, 0644);
    //     }
    //     tmp = tmp->next;
    //     if (errno != 0)
    //         return (errno);
    // }
    // return(0);
}
