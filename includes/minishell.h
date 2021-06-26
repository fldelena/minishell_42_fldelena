#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1

int				ft_check_command(char *m_str);
char			*cut_quote(char *arg);
int				is_n_flag(char *s);
int				ft_work_command(char **arguments, char **env);
void			**line_sort(char **arg);


#endif
