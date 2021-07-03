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

typedef struct s_envp {

	char	**envp;
	char	**var;
	char	**val;

} t_env;

typedef struct s_minishell {

	t_env	*env;

} t_all;

int				ft_check_command(char *m_str);
char			*cut_quote(char *arg);
int				is_n_flag(char *s);
int				ft_work_command(char **arguments, t_all *all);
void			line_sort(char **envp);
char			**add_variable(char **zzz, char **arguments);
char			**del_variable(t_env *env, char **arguments);
char			**arr_copy(char **envp);
void			free_arr(char **arr);
void			make_envp(t_all *all, char **envp);
t_all			*main_struct_malloc(char **envp);

#endif
