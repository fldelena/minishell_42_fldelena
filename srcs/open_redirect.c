#include "../includes/minishell.h"

int ft_open_redirect(t_all *all)
{
    (void)all;
    return (0);
    // t_lst_pipe *tmp;

    // tmp = all->pipe;        // ls | cat -e >> 1.txt > 2.txt    или ls < 1.txt
    // while(tmp->next)
    // {
    //     if (tmp->prev != NULL && tmp->prev->f_red_pip == 2)
    //         // || (tmp->f_red_pip == 0 && tmp->prev != NULL && tmp->prev->f_red_pip > 1)) // если сейчас название файла, но не команда
    //     {
    //         if (tmp->count_red_pip == 1)
    //             tmp->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    //         else
    //             tmp->fd_redirect = open(tmp->command[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
    //     }
    //     // первое слово должно быть командой  (считываем пока не появится символ l)   
    //     if (tmp->prev != NULL && tmp->prev->f_red_pip == 3 && tmp->prev->count_red_pip == 1)
    //         // || (tmp->f_red_pip == 0 && tmp->prev != NULL && tmp->prev->f_red_pip > 1)) // если сейчас название файла, но не команда
    //     {
    //         tmp->fd_redirect = open(tmp->command[0], O_RDONLY, 0644);
    //     }
    //     tmp = tmp->next;
    //     if (errno != 0)
    //         return (errno);
    // }
    // return(0);
}
